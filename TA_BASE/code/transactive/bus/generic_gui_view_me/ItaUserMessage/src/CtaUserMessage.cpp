/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/bus/generic_gui/ItaUserMessage/src/CtaUserMessage.cpp $
  * @author:  San Teo
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * The implementation of ItaUserMessage
  *
  */


#include "bus/generic_gui_view/ItaUserMessage/src/CtaUserMessage.h"
#include "core/threads/src/Thread.h"
#include "core/synchronisation/src/ThreadGuard.h"

using TA_Base_Core::Thread;
using TA_Base_Core::ThreadGuard;

namespace TA_Base_Bus
{

    CtaUserMessage::CtaUserMessage()
	{
	}


    CtaUserMessage::~CtaUserMessage()
	{
        ThreadGuard guard(m_mapLock);
        for (ThreadMessageMap::iterator i = m_map.begin(); i != m_map.end(); i++)
        {
            delete i->second;
            i->second = NULL;
        }
	}


    TAUnicodeString CtaUserMessage::constructMessage(UINT uiMessageID)
    {
        return getMessage().constructMessage(uiMessageID);
    }


    void CtaUserMessage::showMsgBox(UINT uiMessageID)
    {
        getMessage().showMsgBox(uiMessageID);
    }


    ItaUserMessage& CtaUserMessage::operator << (const std::string& arg)
    {
        getMessage() << arg;
        return *this;
    }

/*
    ItaUserMessage& CtaUserMessage::operator << (const TAUnicodeString& arg)
    {
        getMessage() << arg;
        return *this;
    }
*/

    ItaUserMessage& CtaUserMessage::operator << (const bool arg)
    {
        getMessage() << arg;
        return *this;
    }


    ItaUserMessage& CtaUserMessage::operator << (const unsigned long arg)
    {
        getMessage() << arg;
        return *this;
    }
	

    ItaUserMessage& CtaUserMessage::operator << (const short arg)
    {
        getMessage() << arg;
        return *this;
    }


    ItaUserMessage& CtaUserMessage::operator << (const int arg)
    {
        getMessage() << arg;
        return *this;
    }
	

    ItaUserMessage& CtaUserMessage::operator << (const float arg)
    {
        getMessage() << arg;
        return *this;
    }


    void CtaUserMessage::clear()
    {
        getMessage().clearArguments();
    }


    TransActiveMessage& CtaUserMessage::getMessage()
    {
        ThreadGuard guard(m_mapLock);
        unsigned int threadId = Thread::getCurrentThreadId();
        if (m_map.find(threadId) == m_map.end())
        {
            m_map[threadId] = new TransActiveMessage();
        }
        return *m_map[threadId];
    }

};
