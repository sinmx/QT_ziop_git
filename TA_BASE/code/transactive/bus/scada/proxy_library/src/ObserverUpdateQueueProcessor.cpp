/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/bus/scada/proxy_library/src/ObserverUpdateQueueProcessor.cpp $
  * @author:  Andy Parker
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2015/10/09 15:42:35 $
  * Last modified by:  $Author: CM $
  *
  * This class managers the list of observers to be notified when a data point
  * proxy has updated information
  *
  */

#if defined(_MSC_VER)
#pragma warning(disable:4786)
#endif // defined (_MSC_VER)

#include "bus/scada/proxy_library/src/ObserverUpdateQueueProcessor.h"
#include "bus/scada/proxy_library/src/IEntityUpdateEventProcessor.h"
#include "bus/scada/proxy_library/src/ProxyObserverNotifier.h"

#include "core/synchronisation/src/ThreadGuard.h"
#include "core/synchronisation/src/ThreadReadGuard.h"
#include "core/utilities/src/TAAssert.h"
#include "core/utilities/src/DebugUtil.h"

using TA_Base_Core::DebugUtil;

namespace TA_Base_Bus
{
    ObserverUpdateQueueProcessor::ObserverUpdateQueueProcessor(int numberOfWorkers)
    :
    m_updateProcessorPool( NULL ),
    m_logStats( false )
    {
        m_updateProcessorPool =  
			new TA_Base_Core::QueueProcessorPool<ObserverUpdate, 
				TA_Base_Core::QueueProcessorWorker<ObserverUpdate> >(numberOfWorkers, *this);

        // Enable logging of usageCount and observer notification
        if ( true == TA_Base_Core::RunParams::getInstance().isSet ( "LogStatistics" ) )
        {
            m_logStats = true;
        }
    }


    ObserverUpdateQueueProcessor::~ObserverUpdateQueueProcessor()
    {
        delete m_updateProcessorPool;
        m_updateProcessorPool = NULL;
    }

    void ObserverUpdateQueueProcessor::queueNotification(IProxyObserverNotifier* notifier, unsigned long entityKey, ScadaEntityUpdateType updateType)
    {
        boost::shared_ptr<ObserverUpdate> update (new ObserverUpdate);
        update->notifier = notifier;
        update->updateType = updateType;
        m_updateProcessorPool->queueItem(entityKey, update);
    }
    
    void ObserverUpdateQueueProcessor::queueProcessorPoolCallback( boost::shared_ptr<ObserverUpdate> newEvent )
    {
        try
        {
            newEvent.get()->notifier->notifyObservers(newEvent.get()->updateType);
        }
        catch (...) 
        {
            LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugError, "Unknown exception caught when call notifier's notifyObservers");
        }
    }
}
