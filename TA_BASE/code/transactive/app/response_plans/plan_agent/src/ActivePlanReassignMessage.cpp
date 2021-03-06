/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/app/response_plans/plan_agent/src/ActivePlanReassignMessage.cpp $
  *  @author:  Gregg Kirkpatrick
  *  @version: $Revision: #1 $
  *
  *  Last modification: $DateTime: 2015/10/09 15:42:35 $
  *  Last modified by:  $Author: CM $
  *
  *  Implementation of .
  */

#include "app/response_plans/plan_agent/src/ActivePlan.h"
#include "app/response_plans/plan_agent/src/ActivePlanReassignMessage.h"

namespace TA_Base_App
{
	ActivePlanReassignMessage::ActivePlanReassignMessage(const std::string& session, const std::string& pmId) : 
    m_sessionId(session.c_str()),
    m_pmId(pmId.c_str())
	{

	}

	void ActivePlanReassignMessage::execute( ActivePlan& activePlan ) const
	{
		activePlan.reassign(m_sessionId, m_pmId);
	}

} // TA_Base_App
