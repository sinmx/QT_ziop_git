/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/app/response_plans/plan_agent/src/ActivePlanPendingState.cpp $
  *  @author:  Gregg Kirkpatrick
  *  @version: $Revision: #1 $
  *
  *  Last modification: $DateTime: 2015/10/09 15:42:35 $
  *  Last modified by:  $Author: CM $
  *
  *  Implementation of .
  */

#include "app/response_plans/plan_agent/src/ActivePlan.h"
#include "app/response_plans/plan_agent/src/ActivePlanBulletinBoard.h"
#include "app/response_plans/plan_agent/src/ActivePlanExecutingState.h"
#include "app/response_plans/plan_agent/src/ActivePlanPendingState.h"
#include "app/response_plans/common/src/StringConstants.h"

namespace TA_Base_App
{
	int ActivePlanPendingStateImpl::executeNextStep( ActivePlan& activePlan ) const
	{
		// Do nothing.
		ACE_OS::sleep( ACE_Time_Value( 0, 10000 ) );
		return( ActivePlan::NORMAL_NSEM );
	}

	void ActivePlanPendingStateImpl::stop( ActivePlan& activePlan, const std::string& reason ) const
	{
		activePlan.setIsActive( false );


		ActivePlanBulletinBoard::instance()->update( activePlan.getPlan(), TA_Base_Core::STOPPED_ACTIVE_PLAN_STATE, reason );
	}

	void ActivePlanPendingStateImpl::complete( ActivePlan& activePlan ) const
	{
		// Do nothing.
	}

	void ActivePlanPendingStateImpl::pause( ActivePlan& activePlan ) const
	{
		// Do nothing.
	}

	void ActivePlanPendingStateImpl::pauseForOperator( ActivePlan& activePlan ) const
	{
		// Do nothing.
	}

	void ActivePlanPendingStateImpl::resume( ActivePlan& activePlan ) const
	{
		changeState( activePlan, ActivePlanExecutingState::instance() );

		ActivePlanBulletinBoard::instance()->update( activePlan.getPlan(), TA_Base_Core::EXECUTING_ACTIVE_PLAN_STATE, RemarkPlanResumed );
	}

	void ActivePlanPendingStateImpl::reassign( ActivePlan& activePlan, const std::string& sessionId, const std::string& pmId) const
	{
        defaultReassign( activePlan, sessionId, pmId );

    }

	void ActivePlanPendingStateImpl::unassign( ActivePlan& activePlan ) const
	{
		// Do nothing.
	}

    void ActivePlanPendingStateImpl::customiseStep( ActivePlan& activePlan, const TA_Base_Core::StepCustomisableDetail& newDetail ) const
	{
		defaultCustomiseStep( activePlan, newDetail );
	}

} // TA_Base_App
