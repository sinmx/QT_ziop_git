/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/bus/scada/proxy_library/src/DataPointProxy.cpp $
  * @author:  Andy Parker
  * @version: $Revision: #1 $
  *
  * Last modified by:  $Author: CM $
  * Last modification: $DateTime: 2015/10/09 15:42:35 $
  * 
  * This class provides access to a piece of equipment and its associated DataPoints.
  *
  */

#if defined(_MSC_VER)
#pragma warning (disable:4284 4786 4146 4018 4250 4290 4503)
#endif // defined (_MSC_VER)


#include <string> 
#include <algorithm>
#include <limits>
#include <time.h>

#include "bus/scada/proxy_library/src/DataPointProxy.h"
#include "bus/scada/proxy_library/src/DataPointSyncManager.h"
#include "bus/scada/proxy_library/src/DataPointLocalAccess.h"
#include "bus/scada/proxy_library/src/DataPointRemoteAccess.h"
#include "bus/scada/datapoint_library/src/DataPoint.h"

#include "core/data_access_interface/entity_access/src/DataPointEntityData.h"
#include "core/data_access_interface/entity_access/src/EntityAccessFactory.h"
#include "core/data_access_interface/derived_datapoints/src/DerivedDataPointEntityData.h"
#include "core/data_access_interface/derived_datapoints/src/DerivedDataPointAccessFactory.h"
#include "core/data_access_interface/derived_datapoints/src/ConfigConfiguredDerivedState.h"
#include "core/data_access_interface/derived_datapoints/src/IConfigDerivedDataPoint.h"

#include "core/alarm/src/AlarmConstants.h"
#include "core/exceptions/src/ScadaProxyException.h"
#include "core/utilities/src/RunParams.h"
#include "core/utilities/src/TAAssert.h"

using TA_Base_Core::DebugUtil;

namespace TA_Base_Bus
{
	//////////////////////////////////////////////////////////////////////
	// Construction/Destruction
	//////////////////////////////////////////////////////////////////////

	DataPointProxy::DataPointProxy(TA_Base_Core::DataPointEntityDataPtr dpEntityData, 
        DataPointSyncManager& syncManager,
        ObserverUpdateQueueProcessor& observerUpdateQueueProcessor)

        : ProxyObserverNotifier(observerUpdateQueueProcessor),
        m_entityData(dpEntityData),
        m_objAccess(NULL),
        m_dataPointInitialised (false) ,
        m_syncManager(syncManager)

	{
		FUNCTION_ENTRY ("DataPointProxy");
		
		// Setup the initial values
        m_proxyData.isConfigValid = false;
        m_proxyData.isSynchronized = false;

		// Setup the initial values
        loadConfiguration();
		FUNCTION_EXIT;
	}



	DataPointProxy::~DataPointProxy()
	{
		FUNCTION_ENTRY ("~DataPointProxy");
		
		TA_THREADGUARD(m_updateLock); //TD14190, to ensure other functions finished completely.

		try
        {
            if (m_objAccess != NULL)
            {
                delete m_objAccess;
				m_objAccess = NULL;
            }
		}
		catch(...)
		{

		}

		FUNCTION_EXIT;
	}


	void DataPointProxy::updateAgentNotAvailableStatus()
	{
		TA_THREADGUARD(m_updateLock);

		switch (m_proxyData.dynamicData.value.quality)
		{
			// if current quality status is one of these
			case QUALITY_BAD_NO_SPECIFIC_REASON:
			case QUALITY_BAD_CONFIGURATION_ERROR:
			case QUALITY_BAD_DEVICE_FAILURE:
			case QUALITY_BAD_SENSOR_FAILURE:
			case QUALITY_BAD_COMM_FAILURE:
			case QUALITY_BAD_OUT_OF_SERVICE:
			case QUALITY_UNCERTAINTY_NO_SPECIFIC_REASON:
			case QUALITY_UNCERTAINTY_LAST_USABLE_VALUE:
			case QUALITY_UNCERTAINTY_SENSOR_NOT_ACCURATE:
			case QUALITY_UNCERTAINTY_ENG_UNIT_EXCEEDED:
			case QUALITY_UNCERTAINTY_SUB_NORMAL:
			case QUALITY_GOOD_NO_SPECIFIC_REASON:
			case QUALITY_GOOD_LOCAL_OVERRIDE:
			{
				// update quality to this
				m_proxyData.dynamicData.value.quality = QUALITY_BAD_LAST_KNOWN_VALUE;

				break;
			}

			case QUALITY_BAD_LAST_KNOWN_VALUE:
			case QUALITY_BAD_NOT_CONNECTED:
			{
				// keep the current quality status
				break;
			}

			default:
			{
				m_proxyData.dynamicData.value.quality = QUALITY_BAD_NOT_CONNECTED;
				break;
			}
		}
        
        m_proxyData.isConfigValid = true;
        m_proxyData.isSynchronized = false;
    }


	void DataPointProxy::updateInternalState(const TA_Base_Bus::DpCompleteDynamicSyncState& internalState)
	{
		TA_THREADGUARD(m_updateLock);
        
		updateValueStatus(internalState.value);
        updateAlarmStatus(internalState.alarmState);
        updateAlarmAckStatus(internalState.alarmAckState);
        updateAlarmProperties(internalState.alarmProperties);
        updateInhibitedStatus(internalState.inhibitState);
		updateControlStatus(internalState.controlState);
		updateLastOperatorInfo(internalState.lastOperatorInfo);

        m_proxyData.isConfigValid = true;
        m_proxyData.isSynchronized = true;
	}

	void DataPointProxy::updateValueStatus(const TA_Base_Bus::DataPointValue& valueState)
	{
		TA_THREADGUARD(m_updateLock);

        m_proxyData.dynamicData.value = valueState;
	}

    void DataPointProxy::updateAlarmStatus(const TA_Base_Bus::EDataPointAlarms& alarmState)
    {
        TA_THREADGUARD(m_updateLock);

        m_proxyData.dynamicData.alarmState = alarmState;
    }


    void DataPointProxy::updateAlarmAckStatus(const TA_Base_Bus::EScadaAlarmAckState& alarmAckState)
    {
        TA_THREADGUARD(m_updateLock);
        
        m_proxyData.dynamicData.alarmAckState = alarmAckState;
    }
    
    
    void DataPointProxy::updateAlarmProperties(const TA_Base_Bus::AlarmPropertyVect& alarmProperties)
    {
        TA_THREADGUARD(m_updateLock);

        if (m_proxyData.dynamicData.alarmProperties.size() > alarmProperties.size())
        {
            //only update alarm properties partially, only assign the matched items.
            TA_Base_Bus::AlarmPropertyVect::const_iterator itNew;
            for (itNew = alarmProperties.begin(); itNew != alarmProperties.end(); ++ itNew)
            {
                TA_Base_Bus::AlarmPropertyVect::iterator itOld;
                for (itOld = m_proxyData.dynamicData.alarmProperties.begin();
                    itOld != m_proxyData.dynamicData.alarmProperties.end();
                    ++ itOld)
                {
                    if (itOld->type == itNew->type && itOld->enumValue == itNew->enumValue)
                    {
                        itOld->type = itNew->type;
                        itOld->enumValue = itNew->enumValue;
                        itOld->enabled = itNew->enabled;
                        itOld->threshold = itNew->threshold;

                        break;
                    }
                }
            }

            m_proxyData.configData.alarmPropertyVect = m_proxyData.dynamicData.alarmProperties;
        }
        else
        {
            m_proxyData.dynamicData.alarmProperties = alarmProperties;
            m_proxyData.configData.alarmPropertyVect = alarmProperties;
        }
    }
    
    
    void DataPointProxy::updateInhibitedStatus(const TA_Base_Bus::InhibitState& inhibitedState)
	{
		TA_THREADGUARD(m_updateLock);

        m_proxyData.dynamicData.inhibitState = inhibitedState;
	}


	void DataPointProxy::updateControlStatus(const TA_Base_Bus::DataPointControl& controlState)
	{
		TA_THREADGUARD(m_updateLock);

        m_proxyData.dynamicData.controlState = controlState;
	}


	void DataPointProxy::loadConfiguration()
	{
        TA_THREADGUARD(m_updateLock);

        if (m_proxyData.isConfigValid)
        {
            // configuration info already loaded, do nothing
            return;
        }
        
        LOG_GENERIC( SourceInfo, DebugUtil::DebugInfo, "Loading configuration for entity [%u]", getEntityKey());

        m_proxyData.configData.entityKey         = m_entityData->getKey();
        m_proxyData.configData.locationKey       = m_entityData->getLocation();
        m_proxyData.configData.name              = m_entityData->getName();
        m_proxyData.configData.parentKey         = m_entityData->getParent();
        m_proxyData.configData.writable          = m_entityData->getAllowWrite();
        m_proxyData.configData.description       = m_entityData->getDescription();
        m_proxyData.configData.displayOrder      = m_entityData->getDisplayOrder();
        m_proxyData.configData.precision         = m_entityData->getPrecision();
        m_proxyData.configData.typeShortName     = m_entityData->getDataPointTypeShortName();
        m_proxyData.configData.type              = getDpTypeFromString ( m_entityData->getDataPointType() );
        m_proxyData.configData.dataType          = getDpDataTypeFromString ( m_entityData->getDataType() );
        
        // load specific configuration data
        switch ( m_proxyData.configData.type )
        {
            // if this DataPoint is a derived DataPoint
        case TA_Base_Bus::DPT_DERIVED:
        case TA_Base_Bus::DPT_ENUM:
        case TA_Base_Bus::DPT_COMBINED_OUTPUT:
        case TA_Base_Bus::DPT_SAFETY_OUTPUT:
            {
                m_proxyData.configData.enumLabelsMap.clear();
                
                // load enum labels
                TA_Base_Core::IConfigDerivedDataPoint* derivedConfig = TA_Base_Core::DerivedDataPointAccessFactory::getInstance().getDerivedDataPoint(m_entityData->getKey());
                const TA_Base_Core::IConfigDerivedDataPoint::StateMap& stateMap= derivedConfig->getDerivedStates();
                
                for(TA_Base_Core::IConfigDerivedDataPoint::StateMap::const_iterator itr = stateMap.begin(); itr != stateMap.end(); ++ itr)
                {
                    m_proxyData.configData.enumLabelsMap[itr->second->getStateValue()] = itr->second->getStateDescription();
                }
                delete derivedConfig;
				derivedConfig = NULL;
            }
            
            break;
            
        case TA_Base_Bus::DPT_ANALOGUE:
            // load engineering unit conversion
            m_proxyData.configData.engUnits.EngineeringUnitsEnabled = m_entityData->getEngineeringUnitsEnabled();
            m_proxyData.configData.engUnits.Units = m_entityData->getEngineeringUnits();
            m_proxyData.configData.engUnits.HighLimit = m_entityData->getEngineeringLimitHigh();
            m_proxyData.configData.engUnits.LowLimit = m_entityData->getEngineeringLimitLow();
            break;
            
        case TA_Base_Bus::DPT_BOOLEAN:
            m_proxyData.configData.booleanLabels.first = m_entityData->getTrueLabel();
            m_proxyData.configData.booleanLabels.second = m_entityData->getFalseLabel();
			break;
            
        case TA_Base_Bus::DPT_TEXT:
        case TA_Base_Bus::DPT_METERED:
        case TA_Base_Bus::DPT_CALCULATED:
            // no configuration to be loaded for this datapoint type.
            break;
            
        default:
            // do nothing
            LOG_GENERIC( SourceInfo, DebugUtil::DebugError, "Unhandled datapoint type: %d", m_proxyData.configData.type );
            TA_ASSERT( false, "Unhandled datapoint type in DataPointProxyManager::loadDataPointConfiguration" );
            break;
        }

        m_proxyData.dynamicData.value.dpType = m_proxyData.configData.dataType;

		//limin++, for TD20589
		m_proxyData.dynamicData.alarmAckState = TA_Base_Bus::ScadaAlarmUnknown;
		m_proxyData.dynamicData.alarmState = TA_Base_Bus::DptNoAlarm;
		m_proxyData.dynamicData.controlState.controlState = TA_Base_Bus::noControl;
		m_proxyData.dynamicData.controlState.triggerringDpKey = 0;
		m_proxyData.dynamicData.inhibitState.inputInhibit = TA_Base_Bus::NoInputInhibit;
		m_proxyData.dynamicData.inhibitState.outputInhibit = TA_Base_Bus::NoOutputInhibit;
		m_proxyData.dynamicData.value.booleanValue = false;
		m_proxyData.dynamicData.value.enumValue = 0;
		m_proxyData.dynamicData.value.floatValue = 0;
		m_proxyData.dynamicData.value.timeStamp.time = 0;
		m_proxyData.dynamicData.value.timeStamp.millitm = 0;
		m_proxyData.dynamicData.lastOperatorInfo.timeStamp.time = 0;
		m_proxyData.dynamicData.lastOperatorInfo.timeStamp.millitm = 0;
		//++limin, for TD20589

        //set isConfigValid indicator until get complete update or fail to connect to agent
        m_proxyData.isConfigValid = true;
	}


    void DataPointProxy::updateLastOperatorInfo(const TA_Base_Bus::LastOperatorInfo& operatorInfo)
	{
        TA_THREADGUARD(m_updateLock);

        m_proxyData.dynamicData.lastOperatorInfo = operatorInfo;
	}

    IDataPointAccess* DataPointProxy::getObjAccess()
    {
        if (m_objAccess == NULL)
        {
            if (m_syncManager.isLocal(getEntityKey()))
            {
                TA_Base_Bus::IEntity* localEntity = m_syncManager.getLocalEntity(getEntityKey());
                TA_Base_Bus::DataPoint* localDataPoint = dynamic_cast<TA_Base_Bus::DataPoint*>(localEntity);
                
                TA_ASSERT(localDataPoint != NULL, "non-local datapoint is added into local datapoint synchroniser");

                m_objAccess = new DataPointLocalAccess(localDataPoint);
                LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugDebug, "Local datapoint access object created for %u", getEntityKey() );
            }
            else
            {
                m_objAccess = new DataPointRemoteAccess(m_entityData);
                LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugDebug, "Remote datapoint access object created for %u", getEntityKey() );
            }
        }

        return m_objAccess;
    }

    EDataPointAlarms DataPointProxy::stringToDpAlarmType(std::string& typeStr)
    {
        EDataPointAlarms alarmType = DptNoAlarm;
            
        if ( DPTALM_OH == typeStr )
        {
            alarmType = TA_Base_Bus::DptOverScaleHi;
        }
        else if ( DPTALM_OL == typeStr )
        {
            alarmType = TA_Base_Bus::DptOverScaleLo;
        }
        else if ( DPTALM_HIHI == typeStr )
        {
            alarmType = TA_Base_Bus::DptHiHi;
        }
        else if ( DPTALM_HI == typeStr )
        {
            alarmType = TA_Base_Bus::DptHi;
        }
        else if ( DPTALM_LO == typeStr )
        {
            alarmType = TA_Base_Bus::DptLo;
        }
        else if ( DPTALM_LOLO == typeStr )
        {
            alarmType = TA_Base_Bus::DptLoLo;
        }
        else if ( DPTALM_TRUE == typeStr )
        {
            alarmType = TA_Base_Bus::DptBoolTrue;
        }
        else if ( DPTALM_FALSE == typeStr )
        {
            alarmType = TA_Base_Bus::DptBoolFalse;
        }
        else if ( DPTALM_GENERAL == typeStr )
        {
            alarmType = TA_Base_Bus::DptGeneral;
        }
        
        return alarmType;
    }

    
    EDataPointDataType DataPointProxy::getDpDataTypeFromString(std::string dataTypeStr)
    {
        if (DPT_CFG_INT16 == dataTypeStr )
        {
            return TA_Base_Bus::DPT_INT16_TYPE;
        }
        if (DPT_CFG_INT16S == dataTypeStr )
        {
            return TA_Base_Bus::DPT_INT16S_TYPE;
        }
        else if (DPT_CFG_UINT16 == dataTypeStr )
        {
            return TA_Base_Bus::DPT_UINT16_TYPE;
        }
        else if (DPT_CFG_UINT32 == dataTypeStr )
        {
            return TA_Base_Bus::DPT_UINT32_TYPE;
        }
        else if (DPT_CFG_INT32 == dataTypeStr )
        {
            return TA_Base_Bus::DPT_INT32_TYPE;
        }
        else if (DPT_CFG_INT32S == dataTypeStr )
        {
            return TA_Base_Bus::DPT_INT32S_TYPE;
        }
        else if (DPT_CFG_IEEE32 == dataTypeStr )
        {
            return TA_Base_Bus::DPT_IEEE32_TYPE;
        }
        else if (DPT_CFG_DERIVED == dataTypeStr )
        {
            return TA_Base_Bus::DPT_ENUM_TYPE;
        }
        else if (DPT_CFG_BOOL == dataTypeStr )
        {
            return TA_Base_Bus::DPT_BOOL_TYPE;
        }
        else if (DPT_CFG_TEXT == dataTypeStr )
        {
            return TA_Base_Bus::DPT_TEXT_TYPE;
        }
        else
        {
            return TA_Base_Bus::DPT_NULL_TYPE;
        }
    }
    
    
    EDataPointType DataPointProxy::getDpTypeFromString(std::string typeStr)
    {
        if ( DPT_BOOLEAN_TYPE_STRING == typeStr )
        {
            return TA_Base_Bus::DPT_BOOLEAN;
        }
        else if ( DPT_TEXT_TYPE_STRING == typeStr )
        {
            return TA_Base_Bus::DPT_TEXT;
        }
        else if ( DPT_ANALOGUE_TYPE_STRING == typeStr )
        {
            return TA_Base_Bus::DPT_ANALOGUE;
        }
        else if ( DPT_DERIVED_TYPE_STRING == typeStr )
        {
            return TA_Base_Bus::DPT_DERIVED;
        }
        else if ( DPT_COMBINED_OUTPUT_TYPE_STRING == typeStr )
        {
            return TA_Base_Bus::DPT_COMBINED_OUTPUT;
        }
        else if ( DPT_SAFETY_OUTPUT_TYPE_STRING == typeStr )
        {
            return TA_Base_Bus::DPT_SAFETY_OUTPUT;
        }
        else if ( DPT_METERED_ANALOGUE_TYPE_STRING == typeStr )
        {
            return TA_Base_Bus::DPT_METERED;
        }
        else if ( DPT_CALCULATED_TYPE_STRING == typeStr )
        {
            return TA_Base_Bus::DPT_CALCULATED;
        }
        else if ( DPT_ENUM_TYPE_STRING == typeStr )
        {
            return TA_Base_Bus::DPT_ENUM;
        }
        else
        {
            return TA_Base_Bus::DPT_UNKNOWN_TYPE;
        }
    }
    
}



