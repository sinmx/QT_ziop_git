#ifndef ACTIVEPLANPAUSEDSTATE_H_INCLUDED
#define ACTIVEPLANPAUSEDSTATE_H_INCLUDED

/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/app/response_plans/plan_agent/src/ActivePlanPausedState.h $
  *  @author:  Gregg Kirkpatrick
  *  @version: $Revision: #1 $
  *
  *  Last modification: $DateTime: 2015/10/09 15:42:35 $
  *  Last modified by:  $Author: CM $
  *
  *  <description>
  */

#include <string>

#include "ace/Singleton.h"

#include "app/response_plans/plan_agent/src/ActivePlanState.h"

namespace TA_Base_Core
{
    struct StepCustomisableDetail;
}

namespace TA_Base_App
{
    class ActivePlan;

	//Class declaration
	class ActivePlanPausedStateImpl : public ActivePlanState
	{
	// Public methods
	public:

		friend class ACE_Singleton<ActivePlanPausedStateImpl, ACE_Recursive_Thread_Mutex>;

		virtual int executeNextStep( ActivePlan& activePlan ) const;

		virtual void stop( ActivePlan& activePlan, const std::string& reason ) const;
		virtual void complete( ActivePlan& activePlan ) const;
		virtual void pause( ActivePlan& activePlan ) const;
		virtual void pauseForOperator( ActivePlan& activePlan ) const;
		virtual void resume( ActivePlan& activePlan ) const;
		virtual void reassign( ActivePlan& activePlan, const std::string& sessionId, const std::string& pmId ) const;
		virtual void unassign( ActivePlan& activePlan ) const;
        virtual void customiseStep( ActivePlan& activePlan, const TA_Base_Core::StepCustomisableDetail& newDetail ) const;

	private:
		ActivePlanPausedStateImpl(){}
		~ActivePlanPausedStateImpl(){}
		ActivePlanPausedStateImpl( const ActivePlanPausedStateImpl& );
		ActivePlanPausedStateImpl& operator=( const ActivePlanPausedStateImpl& );

	}; // ActivePlanPausedState
	typedef ACE_Singleton<ActivePlanPausedStateImpl, ACE_Recursive_Thread_Mutex> ActivePlanPausedState;
}; // TA_Base_App

#endif // ACTIVEPLANPAUSEDSTATE_H_INCLUDED
