#ifndef ACTIVEPLANSTOPMESSAGE_H_INCLUDED
#define ACTIVEPLANSTOPMESSAGE_H_INCLUDED

/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/app/response_plans/plan_agent/src/ActivePlanStopMessage.h $
  *  @author:  Gregg Kirkpatrick
  *  @version: $Revision: #1 $
  *
  *  Last modification: $DateTime: 2015/10/09 15:42:35 $
  *  Last modified by:  $Author: CM $
  *
  *  <description>
  */

#include <string>

#include "app/response_plans/plan_agent/src/IActivePlanMessage.h"

namespace TA_Base_App
{
    class ActivePlan;

	//Class declaration
	class ActivePlanStopMessage : public IActivePlanMessage
	{
	// Public methods
	public:
        ActivePlanStopMessage(const std::string& reason);

		virtual void execute( ActivePlan& activePlan ) const;
	
	private:
		ActivePlanStopMessage& operator=( const ActivePlanStopMessage& );
		ActivePlanStopMessage( const ActivePlanStopMessage& );

        std::string m_reason;

	}; // ActivePlanStopMessage
}; // TA_Base_App

#endif // ACTIVEPLANSTOPMESSAGE_H_INCLUDED
