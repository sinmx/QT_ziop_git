/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/app/response_plans/plan_agent/src/ActivePlanPausedState.cpp $
  *  @author:  Gregg Kirkpatrick
  *  @version: $Revision: #1 $
  *
  *  Last modification: $DateTime: 2015/10/09 15:42:35 $
  *  Last modified by:  $Author: CM $
  *
  *  Implementation of .
  */

#include "app/response_plans/plan_agent/src/PlanAgentUser.h"
#include "app/response_plans/plan_agent/src/ActivePlan.h"
#include "app/response_plans/plan_agent/src/ActivePlanBulletinBoard.h"
#include "app/response_plans/plan_agent/src/ActivePlanExecutingState.h"
#include "app/response_plans/plan_agent/src/ActivePlanPausedState.h"
#include "app/response_plans/common/src/StringConstants.h"

namespace TA_Base_App
{
	int ActivePlanPausedStateImpl::executeNextStep( ActivePlan& activePlan ) const
	{
		// Do nothing.
		ACE_OS::sleep( ACE_Time_Value( 0, PlanAgentUser::getInstance()->getPausedPlanSleepTime ()) );
		return( ActivePlan::INTERLOCKED_NSEM );
	}

	void ActivePlanPausedStateImpl::stop( ActivePlan& activePlan, const std::string& reason ) const
	{
		activePlan.setIsActive( false );

		ActivePlanBulletinBoard::instance()->update( activePlan.getPlan(), TA_Base_Core::STOPPED_ACTIVE_PLAN_STATE, reason );
	}

	void ActivePlanPausedStateImpl::complete( ActivePlan& activePlan ) const
	{
		// Do nothing.
	}

    void ActivePlanPausedStateImpl::pause( ActivePlan& activePlan ) const
	{
		// Do nothing.
	}

	void ActivePlanPausedStateImpl::pauseForOperator( ActivePlan& activePlan ) const
	{
		// Do nothing.
	}

	void ActivePlanPausedStateImpl::resume( ActivePlan& activePlan ) const
	{
		changeState( activePlan, ActivePlanExecutingState::instance() );

        // If interactive step timeout and paused, the lock should release when operator resume plan
        activePlan.setOperatorResponseInterlock(false);

        ActivePlanBulletinBoard::instance()->updateStepStartTime( activePlan.getPlan(), ACE_OS::gettimeofday() );
		ActivePlanBulletinBoard::instance()->update( activePlan.getPlan(), TA_Base_Core::EXECUTING_ACTIVE_PLAN_STATE, RemarkPlanResumed );
	}

	void ActivePlanPausedStateImpl::reassign( ActivePlan& activePlan, const std::string& sessionId, const std::string& pmId ) const
	{
		defaultReassign( activePlan, sessionId, pmId );
	}

	void ActivePlanPausedStateImpl::unassign( ActivePlan& activePlan ) const
	{
		defaultUnassign( activePlan );
	}

    void ActivePlanPausedStateImpl::customiseStep( ActivePlan& activePlan, const TA_Base_Core::StepCustomisableDetail& newDetail ) const
	{
		defaultCustomiseStep( activePlan, newDetail );
	}
} // TA_Base_App
