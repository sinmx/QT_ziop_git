#ifndef CONTROLEXECUTIVE_H_INCLUDED
#define CONTROLEXECUTIVE_H_INCLUDED

/**
 * The source code in this file is the property of
 * Ripple Systems and is not for redistribution in any form.
 * 
 * Source:    $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/app/security/duty_agent/src/ControlExecutive.h $
 * @author:   Gregg Kirkpatrick
 * @version:  $Revision: #1 $
 *
 * Last modification: $DateTime: 2015/10/09 15:42:35 $
 * Last modified by:  $Author: CM $
 *
 * Used to allow different behaviour for the execution of Agent methods between
 * Control and Monitor modes.
 */

#include "app/security/duty_agent/src/IDutyAgentExecutive.h"

namespace TA_Base_App
{ 
	class ControlExecutive : public IDutyAgentExecutive
    {
    public:
		
		virtual void execute(IDutyAgentCommand& command, TA_Base_Bus::RightsLibrary& rightsLib, ta_uint32 resourceKey, bool checkRights = true ) const;
		
    };
}

#endif // CONTROLEXECUTIVE_H_INCLUDED
