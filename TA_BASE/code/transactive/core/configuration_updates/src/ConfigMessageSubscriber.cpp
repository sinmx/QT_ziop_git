/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/core/configuration_updates/src/ConfigMessageSubscriber.cpp $
  * @author:  San Teo
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2015/10/09 15:42:35 $
  * Last modified by:  $Author: CM $
  *
  * This class receives and sends config update messages.
  */

#if defined(_MSC_VER)
    #pragma warning(disable:4786)
#endif // defined (_MSC_VER)

#include "core/configuration_updates/src/ConfigMessageSubscriber.h"
#include "core/configuration_updates/src/OnlineUpdateListener.h"
#include "core/configuration_updates/src/ConfigUpdateDetails.h"
#include "core/message/src/MessageSubscriptionManager.h"
#include "core/message/src/MessagePublicationManager.h"
#include "core/message/src/ConfigUpdateMessageSender.h"
#include "core/message/types/ConfigUpdate_MessageTypes.h"
#include "core/utilities/src/TAAssert.h"
#include "core/utilities/src/DebugUtil.h"
#include "core/versioning/src/Version.h"


namespace TA_Base_Core
{
    ConfigMessageSubscriber::~ConfigMessageSubscriber()
    {
        ThreadGuard guard(m_senderLock);
        // should try unsubscribe before it gets deleted.
        unsubscribe();
        delete m_sender;
        m_sender = NULL;
    }


    void ConfigMessageSubscriber::subscribe()
    {
        FUNCTION_ENTRY("subscribe");

        ThreadGuard guard(m_senderLock);

        // if we want to subscribe and are not currently subscribing,
        // then subscribe
        if (m_sender == NULL)
        {
            LOG(SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugInfo, "Subscribing to the config update");

            // subscribe to the ConfigUpdate Context
            MessageSubscriptionManager::getInstance().subscribeToConfigUpdateMessage(ConfigUpdate::Context, this);

            // get the context that we've subscribed to
            m_sender = MessagePublicationManager::getInstance().getConfigUpdateMessageSender(ConfigUpdate::Context);
        }

        FUNCTION_EXIT;
    }


    void ConfigMessageSubscriber::unsubscribe()
    {
        FUNCTION_ENTRY("unsubscribe");

        ThreadGuard guard(m_senderLock);

        // if we're currently subscribing and we want to
        // stop subscribing, then unsubscribe
        if (m_sender != NULL)
        {
            LOG(SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugInfo, "Unsubscribing to the config update");

            // stop subscribing
            MessageSubscriptionManager::getInstance().unsubscribeToMessages(this);

            LOG(SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugInfo, "Successfully unsubscribed");

            delete m_sender;
            m_sender = NULL;
        }

        FUNCTION_EXIT;
    }


    bool ConfigMessageSubscriber::isSubscribing() const
    {
        ThreadGuard guard(m_senderLock);
        return (m_sender != NULL);
    }


    void ConfigMessageSubscriber::generateEntityUpdateMessage(
        ConfigUpdateDetails& update)
    {
        FUNCTION_ENTRY("generateEntityUpdateMessage");

        TA_ASSERT(update.getType() == TA_Base_Core::ENTITY_OWNER, "Only entity owner could generate entity update");

        LOG(SourceInfo, DebugUtil::GenericLog,
            DebugUtil::DebugInfo,
            "Regenerating config update message to ConfigEntity, key=%d",
            update.getKey());

        // send an update message
        m_sender->sendConfigUpdateMessage(
            ConfigUpdate::ConfigEntity,
            update.getKey(),
            update.getModifications(),
            update.getChangedParams(),
            NULL);

        FUNCTION_EXIT;
    }


    void ConfigMessageSubscriber::receiveSpecialisedMessage(
        const ConfigUpdateMessageCorbaDef& message)
    {
        FUNCTION_ENTRY("receiveSpecialisedMessage");

        std::string messageTypeKey(message.messageTypeKey);

        LOG(SourceInfo, DebugUtil::GenericLog,
            DebugUtil::DebugDebug,
            "Update is: object type = %s, key = %d, modification type = %d",
            messageTypeKey.c_str(),
            message.assocEntityKey,
            message.modificationType);

        // if there is no object type with its key matching this
        // message's type key, then just return
        if (!m_messageObjectTypeMap.isMessageValid(messageTypeKey))
        {
            LOG2(SourceInfo, DebugUtil::DebugWarn, "Unrecognised message type %s for entity key %d, ignore",
                 messageTypeKey.c_str(), message.assocEntityKey);

            FUNCTION_EXIT;
            return;
        }

        // create ConfigUpdateDetails
        ConfigUpdateDetails update(message, m_messageObjectTypeMap.getObjectType(messageTypeKey));

        // get the ConfigMessageSubscriber to sort out whether there is any interest on the update
        OnlineUpdateListener::getInstance().processUpdate(update);

        FUNCTION_EXIT;
    }
}
