/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/bus/scada/proxy_library/src/DataPointProxy_Write.cpp $
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
#pragma warning(disable:4786)
#pragma warning(disable:4250)
#endif // defined (_MSC_VER)

#include <string> 
#include <limits>
#include <time.h>

#include "bus/scada/proxy_library/src/DataPointProxy.h"
#include "bus/scada/proxy_library/src/DataPointSyncManager.h"
#include "bus/scada/common_library/src/DpValue.h"

#include "core/data_access_interface/entity_access/src/DataPointEntityData.h"
#include "core/exceptions/src/ScadaProxyException.h"
#include "core/utilities/src/TAAssert.h"

using TA_Base_Core::DebugUtil;

namespace TA_Base_Bus
{


	void DataPointProxy::setMeteredCorrectionValue(double value, std::string sessionId)
	{
        if(!m_proxyData.isSynchronized)
        {
            std::string text = "Info: Agent is not connected for DataPoint " + m_entityData->getName() + ".";
            LOG(SourceInfo, TA_Base_Core::DebugUtil::GenericLog, TA_Base_Core::DebugUtil::DebugInfo,
                "setMeteredCorrectionValue() - %s - %s", m_entityData->getName().c_str(), text.c_str());
            
            TA_THROW(TA_Base_Core::ScadaProxyException (text));
        }
        
		if (getType()!= DPT_METERED)
		{
			std::string text = "Error: DataPoint \"" + m_proxyData.configData.description + "\" is not a metered datapoint - adjustment not possible.";
			LOG(SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugDebug, 
				"setMeteredCorrectionValue() - %s - %s", m_entityData->getName().c_str(), text.c_str());

			TA_THROW(TA_Base_Core::ScadaProxyException(text));
		}

         getObjAccess()->setMeteredCorrectionValue(sessionId, value);
			
	}



	void DataPointProxy::setOverrideEnableStatus(bool enable, std::string sessionId)
	{
        if(!m_proxyData.isSynchronized)
        {
            std::string text = "Info: Agent is not connected for DataPoint " + m_entityData->getName() + ".";
            LOG(SourceInfo, TA_Base_Core::DebugUtil::GenericLog, TA_Base_Core::DebugUtil::DebugInfo,
                "setOverrideEnableStatus() - %s - %s", m_entityData->getName().c_str(), text.c_str());
            
            TA_THROW(TA_Base_Core::ScadaProxyException (text));
        }
        
		getObjAccess()->setIsForcedState(sessionId, enable);
	}


	void DataPointProxy::setManuallyOverrideValue ( const std::string & value, const std::string & sessionId )
	{
        if(!m_proxyData.isSynchronized)
        {
            std::string text = "Info: Agent is not connected for DataPoint " + m_entityData->getName() + ".";
            LOG(SourceInfo, TA_Base_Core::DebugUtil::GenericLog, TA_Base_Core::DebugUtil::DebugInfo,
                "setManuallyOverrideValue() - %s - %s", m_entityData->getName().c_str(), text.c_str());
            
            TA_THROW(TA_Base_Core::ScadaProxyException (text));
        }
        
		// convert the specified value from string to DataPointValue
		DpValue dpValue (value, m_proxyData.configData.dataType,
						 m_proxyData.configData.enumLabelsMap, 
                         m_proxyData.configData.booleanLabels,
						 m_proxyData.configData.precision);

		getObjAccess()->setForcedStateWithValue (sessionId, dpValue.getDataPointValue() );
	}


	void DataPointProxy::setAlarmProperties ( const AlarmProperty& newAlarmProperty, const std::string & sessionId )
	{
        if(!m_proxyData.isSynchronized)
        {
            std::string text = "Info: Agent is not connected for DataPoint " + m_entityData->getName() + ".";
            LOG(SourceInfo, TA_Base_Core::DebugUtil::GenericLog, TA_Base_Core::DebugUtil::DebugInfo,
                "setAlarmProperties() - %s - %s", m_entityData->getName().c_str(), text.c_str());
            
            TA_THROW(TA_Base_Core::ScadaProxyException (text));
        }
        
		getObjAccess()->setAlarmProperty (sessionId, newAlarmProperty );
	}


	void DataPointProxy::setOutputInhibitStatus(EOutputInhibitState inhibit, std::string sessionId)
	{
        if(!m_proxyData.isSynchronized)
        {
            std::string text = "Info: Agent is not connected for DataPoint " + m_entityData->getName() + ".";
            LOG(SourceInfo, TA_Base_Core::DebugUtil::GenericLog, TA_Base_Core::DebugUtil::DebugInfo,
                "setOutputInhibitStatus() - %s - %s", m_entityData->getName().c_str(), text.c_str());
            
            TA_THROW(TA_Base_Core::ScadaProxyException (text));
        }
        
		if (!m_proxyData.configData.writable)
		{
			std::string text = "Error:DataPoint \"" + m_proxyData.configData.description + "\" is an input DataPoint - control inhibit not possible.";
			LOG(SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugDebug, 
				"setControlInhibitStatus() - %s - %s", m_entityData->getName().c_str(), text.c_str());

			TA_THROW(TA_Base_Core::ScadaProxyException(text));
		}

		getObjAccess()->setOutputInhibitState(sessionId, inhibit);
	}


	void DataPointProxy::setValue(std::string value, std::string sessionId, unsigned long triggeringEntityKey, char * triggeringEntityValue, bool auditEventLoggingEnabled) //TD15649
	{
        if(!m_proxyData.isSynchronized)
        {
            std::string text = "Info: Agent is not connected for DataPoint " + m_entityData->getName() + ".";
            LOG(SourceInfo, TA_Base_Core::DebugUtil::GenericLog, TA_Base_Core::DebugUtil::DebugInfo,
                "setValue() - %s - %s", m_entityData->getName().c_str(), text.c_str());
            
            TA_THROW(TA_Base_Core::ScadaProxyException (text));
        }
        
		if (!m_proxyData.configData.writable)
		{
			std::string text = "Error:DataPoint \"" + m_proxyData.configData.description + "\" is an input DataPoint - writing is not possible.";
			LOG(SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugDebug, 
				"setControlInhibitStatus() - %s - %s", m_entityData->getName().c_str(), text.c_str());

            return;
		}

        // convert the specified value from string to DataPointValue
		DpValue dpValue (value, m_proxyData.configData.dataType,
                        m_proxyData.configData.enumLabelsMap,
                        m_proxyData.configData.booleanLabels,
                        m_proxyData.configData.precision);

        DataPointValue dpvalue = dpValue.getDataPointValue();

        if (auditEventLoggingEnabled)
        {
            getObjAccess()->writeDataPointValue(sessionId, dpvalue, triggeringEntityKey, triggeringEntityValue);
        }
        else
        {
            getObjAccess()->writeDataPointValueWithoutLoggingEvent(sessionId, dpvalue, triggeringEntityKey, triggeringEntityValue);
        }
	}

	void DataPointProxy::setBoolValue(bool value, std::string sessionId)
	{
        if(!m_proxyData.isSynchronized)
        {
            std::string text = "Info: Agent is not connected for DataPoint " + m_entityData->getName() + ".";
            LOG(SourceInfo, TA_Base_Core::DebugUtil::GenericLog, TA_Base_Core::DebugUtil::DebugInfo,
                "setBoolValue() - %s - %s", m_entityData->getName().c_str(), text.c_str());
            
            TA_THROW(TA_Base_Core::ScadaProxyException (text));
        }
        
		// Get DataPoint type
		if (m_proxyData.configData.dataType!=DPT_BOOL_TYPE)
		{
			std::string text = "Error:DataPoint is not boolean";
			LOG(SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugDebug, 
				"setBoolValue() - %s - %s", m_entityData->getName().c_str(), text.c_str());

			TA_THROW(TA_Base_Core::ScadaProxyException(text));
		}

		if (!m_proxyData.configData.writable)
		{
			std::string text = "Error:DataPoint \"" + m_proxyData.configData.description + "\" is an input DataPoint - writing is not possible.";
			LOG(SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugDebug, 
				"setBoolValue() - %s - %s", m_entityData->getName().c_str(), text.c_str());

//			TA_THROW(TA_Base_Core::ScadaProxyException(text));
		}

		TA_Base_Bus::DataPointValue dataPointValue;

        dataPointValue.dpType = m_proxyData.configData.dataType;
		dataPointValue.booleanValue = value;  // = true;

        getObjAccess()->writeDataPointValue(sessionId, dataPointValue, 0, "");
    }
	
	void DataPointProxy::setAnalogueValue(double value, std::string sessionId)
	{
        if(!m_proxyData.isSynchronized)
        {
            std::string text = "Info: Agent is not connected for DataPoint " + m_entityData->getName() + ".";
            LOG(SourceInfo, TA_Base_Core::DebugUtil::GenericLog, TA_Base_Core::DebugUtil::DebugInfo,
                "setAnalogueValue() - %s - %s", m_entityData->getName().c_str(), text.c_str());
            
            TA_THROW(TA_Base_Core::ScadaProxyException (text));
        }
        
		// Get DataPoint type
		// wenching++
		// Should throw for invalid analogue datapoints, conditions check revised.
		if (m_proxyData.configData.dataType!=DPT_INT16_TYPE &&
				 m_proxyData.configData.dataType!=DPT_INT16S_TYPE &&
				 m_proxyData.configData.dataType!=DPT_UINT16_TYPE &&
				 m_proxyData.configData.dataType!=DPT_UINT32_TYPE &&
			 	 m_proxyData.configData.dataType!=DPT_INT32_TYPE &&
				 m_proxyData.configData.dataType!=DPT_INT32S_TYPE && 
				 m_proxyData.configData.dataType!=DPT_IEEE32_TYPE)
		// ++wenching
		{
			std::string text = "Error:DataPoint is not Analogue";
			LOG(SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugDebug, 
				"setAnalogueValue() - %s - %s", m_entityData->getName().c_str(), text.c_str());

			TA_THROW(TA_Base_Core::ScadaProxyException(text));
		}

		if (!m_proxyData.configData.writable)
		{
			std::string text = "Error:DataPoint \"" + m_proxyData.configData.description + "\" is an input DataPoint - writing is not possible.";
			LOG(SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugDebug, 
				"setAnalogueValue() - %s - %s", m_entityData->getName().c_str(), text.c_str());

//			TA_THROW(TA_Base_Core::ScadaProxyException(text));
		}

		TA_Base_Bus::DataPointValue dataPointValue;

        dataPointValue.dpType = m_proxyData.configData.dataType;
        dataPointValue.floatValue = value;  // = true;
        
        getObjAccess()->writeDataPointValue(sessionId, dataPointValue, 0, "");
	}
	
	void DataPointProxy::setInputInhibitStatus(EInputInhibitState inputInhibit, std::string sessionId)
	{
        if(!m_proxyData.isSynchronized)
        {
            std::string text = "Info: Agent is not connected for DataPoint " + m_entityData->getName() + ".";
            LOG(SourceInfo, TA_Base_Core::DebugUtil::GenericLog, TA_Base_Core::DebugUtil::DebugInfo,
                "setInputInhibitStatus() - %s - %s", m_entityData->getName().c_str(), text.c_str());
            
            TA_THROW(TA_Base_Core::ScadaProxyException (text));
        }
        
		if (m_proxyData.configData.writable)
		{
			std::string text = "Error:DataPoint \"" + m_proxyData.configData.description + "\" is an output DataPoint - input inhibit not possible.";
			LOG(SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugDebug, 
				"setInputInhibitStatus() - %s - %s", m_entityData->getName().c_str(), text.c_str());

			TA_THROW(TA_Base_Core::ScadaProxyException(text));
		}	

        getObjAccess()->setInputInhibitState(sessionId, inputInhibit);
	}
}


