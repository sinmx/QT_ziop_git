// TransActiveMessage.h: interface for the TransActiveMessage class.
//
//////////////////////////////////////////////////////////////////////
/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/bus/generic_gui_view/src/TransActiveMessage.h $
  * @author:  Brett Zimmerman
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * Standard message box format, display and logging functions
  *    Important Note : Class TransActiveMessage is not thread safe.
  */
#pragma once
#pragma warning(disable:4786)
#include "bus/TA_MessageResource/Resource.h"
#include "bus/unicode_common_lib/src/TAUnicodeString.h"
#include "core/synchronisation/src/ReEntrantThreadLockable.h"
#include <boost/lexical_cast.hpp>
#include <QtCore/QObject>
#include <sstream>
#include <vector>
#include <sstream>
#include <vector>

namespace TA_Base_Bus
{
    struct TransActiveMessageConfig;

    class TransActiveMessage  : public QObject
    {
        Q_OBJECT

    public:

        /**
          * ConstructMessage
          *
          * @param uiMessageID - Resource identifier of the string to display
          *
          * Constructs a formatted string using the loaded string resource identifier
          * and the pre-input arguments.
          * Format of the string table entry must match - MessageBoxStyle|HelpID|AuditInteraction|Message
          */
        std::string constructMessage(int uiMessageID);

        /**
          * ShowMsgBox
          *
          * @param uiMessageID - Resource identifier of the string to display
          *
          * Displays a message box with text and appearance loaded from the input string resource
          * identifier. Returns the result of ::MessageBox, 0 upon failure.
          */
        int showMsgBox(int uiMessageID,  std::string caption = "");   //TD19032 Coreteam

        /**
          * Constructor
          *
          * Creates a TransActiveMessage object loading TA_MessageResource.dll from the current directory
          * with a language matching the users default language.
          */
        TransActiveMessage();

        /**
          * Constructor
          *
          * @param hResourceDll - Handle of the resource instance.
          * @param lcidLang - LCID of the language to load from the resource library.
          *
          * Creates a TransActiveMessage object with its resource library set to hResourceDll and the
          * language set to lcidLang
          */
        /*TransActiveMessage(HINSTANCE hResourceDll, LCID lcidLang);*/

        /**
          * Destructor
          *
          * Free resource library if loaded and destroy TransActiveMessage object.
          */
        virtual ~TransActiveMessage();

        /**
          * Generic parameter vector input operators
          *
          * @param Arg - Parameter to be inserted into the message arguments member vector.
          *
          * Adds the input paramater to arguments for the message.
          */
        template<typename T> inline TransActiveMessage& operator << (T arg)
        { try { m_args.push_back(boost::lexical_cast<std::string>(arg)); } catch (...) {} return *this; }

        template<> inline TransActiveMessage& operator << (const std::string& arg)
        { m_args.push_back(arg); return *this; }

        template<> inline TransActiveMessage& operator << (const char*& arg)
        { m_args.push_back(arg); return *this; }

        template<> inline TransActiveMessage& operator << (const QString& arg)
        { m_args.push_back(arg.toStdString()); return *this; }

        /**
          * ClearArguments
          *
          * Empties the member vector of message arguments
          */
        inline void clearArguments() { m_args.clear(); }

        /**
          * closeAllMessages
          *
          * Close all popup windows
          *
          */
        static void closeAllMessages();

    private:

        /**
          * GetRawMessage
          *
          * @param uiMessageID - Resource identifier of the string to load.
          * @param sMessage - [OUT] Address of the string to load the message into.
          *
          * @return - true if successful, false otherwise.
          *
          * Loads the string resource from m_hResourceDll into sMessage.
          */
        bool getRawMessage(int uiMessageID, std::string& sMessage);

        /**
          * ParseRawMessage
          *
          * @param sRawMessage - [IN] Message in its raw format. Must have format - MessageBoxStyle|HelpID|Message
          * @param uiMsgBoxType - [OUT] UINT to hold the MessageBox style extracted from the raw message string.
          * @param uiHelpID - [OUT] UINT to hold the help topic identifier extracted from the raw message string.
          * @param bAudit - [OUT] bool that indicates whether the message needs to be logged or not
          * @param sMessage - [OUT] TAUnicodeString to take the message component of the raw message string.
          *
          * @return - true if successful, false otherwise.
          *
          * This functions breaks the raw message into its three attributes.
          */
        bool parseRawMessage(const std::string& sRawMessage, int& uiMsgBoxType, int& uiHelpID, bool& bAudit, std::string& sMessage);

        /**
          * ConstructMessage
          *
          * @param sRawMessage - [IN/OUT] String with place markers for args. Contains formated string on exit.
          *
          * @return - true if successful, false otherwise.
          *
          * Constructs a formated message using the pre input arguments.
          */
        std::string constructMessage(std::string sRawMessage);

        /**
          * LogMessage
          *
          * @param pszCaption - Caption from the message box.
          * @param pszMessage - Message from the message box.
          * @param uiResult - Exit result returned by ::MessageBox.
          * @param bAuditEvent - Raise an audit event
          *
          * @return - true if successful, false otherwise.
          *
          * Adds the information passed in to the log when the logging level is set to info.
          */
        //bool logMessage(std::string& pszCaption, std::string& pszMessage, int uiResult, bool bAuditEvent);

        /**
          * SetHelpContext
          *
          * @param uiHelp - Context sensitive help identifer to set.
          * @param pdwContext - [OUT] Context pointer used to restore the help context for the App.
          * @param dwPrevContext - [OUT] Previous help identifier used to restore the help.
          *
          * @return - Returns true if the help context could be set, fale otherwise.
          *
          * Sets the help context to the input topic identifier. ResetHelpContext must be called
          * to restore the help context to its previous state.
          */
        bool setHelpContext() {};

        /**
          * ResetHelpContext
          *
          * @param pdwContext - Context pointer for the App.
          * @param dwPrevContext - Previous help identifier.
          *
          * Restores the help context to the state prior to the call to SetHelpContext
          *
          */
        void resetHelpContext() {};

        /**
          * ReformatCurlyBraces
          *
          * @param sMessage - [IN/OUT] String to alter.
          *
          * Replaces '{{' with '{', and '}}' with '}'.
          */
        void reformatCurlyBraces(std::string& sMessage);

        /**
          * FormatCaption
          *
          * @param sCaption - [OUT] Formated caption.
          * @param uiMessageID - Message identifer added to the caption
          *
          * Creates a message box caption with a format ApplicationName - [MessageIdentifier].
          */
        void formatCaption(std::string& sCaption, int uiMessageID);

    private slots:

        /**
        * DoMsgBox
        *
        * @param pszCaption - String to display in the title bar of the message box
        * @param pszMessage - String to display in the body of the message box.
        * @param uiMsgBoxType - Message box style options e.g MB_YESNO- see MSDN ::MessageBox for details
        * @param uiHelpID - Help topic identifier.
        * @param bAuditEvent - Raise an Audit Event
        *
        * Displays a message box with text and appearance loaded from the input string resource
        * identifier. Returns the result of ::MessageBox, 0 upon failure.
        *
        */
        //void doMsgBoxSlot(std::string pszCaption, std::string pszMessage, int uiMsgBoxType,  int* ret, int uiHelpID,
        //	bool bAuditEvent);
        void doMsgBox(int uiMessageID,  std::string caption, int* ret, bool bAuditEvent = false);

    private:

        TransActiveMessage(const TransActiveMessage& rhs);
        TransActiveMessage& operator=(const TransActiveMessage&);

        void throwMessageResourceException(const char* formatStr, const std::string& rawMessage);

        // Type safe message arguments vector
        std::vector<std::string> m_args;

        std::string m_sResourceFilePath;
        // File name and path of the resource dll to load

        TransActiveMessageConfig* m_config;
    };
}

inline int showMsgBox(int uiMessageID)
{
    return TA_Base_Bus::TransActiveMessage().showMsgBox(uiMessageID);
}

template<typename T1>
int showMsgBox(int uiMessageID, const T1& p1)
{
    TA_Base_Bus::TransActiveMessage msg;
    msg << p1;
    return msg.showMsgBox(uiMessageID);
}

template<typename T1, typename T2>
int showMsgBox(int uiMessageID, const T1& p1, const T2& p2)
{
    TA_Base_Bus::TransActiveMessage msg;
    msg << p1 << p2;
    return msg.showMsgBox(uiMessageID);
}

template<typename T1, typename T2, typename T3>
int showMsgBox(int uiMessageID, const T1& p1, const T2& p2, const T3& p3)
{
    TA_Base_Bus::TransActiveMessage msg;
    msg << p1 << p2 << p3;
    return msg.showMsgBox(uiMessageID);
}

template<typename T1, typename T2, typename T3, typename T4>
int showMsgBox(int uiMessageID, const T1& p1, const T2& p2, const T3& p3, const T4& p4)
{
    TA_Base_Bus::TransActiveMessage msg;
    msg << p1 << p2 << p3 << p4;
    return msg.showMsgBox(uiMessageID);
}

template<typename T1, typename T2, typename T3, typename T4, typename T5>
int showMsgBox(int uiMessageID, const T1& p1, const T2& p2, const T3& p3, const T4& p4, const T5& p5)
{
    TA_Base_Bus::TransActiveMessage msg;
    msg << p1 << p2 << p3 << p4 << p5;
    return msg.showMsgBox(uiMessageID);
}
