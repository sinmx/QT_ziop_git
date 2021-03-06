/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/app/response_plans/plan_agent/src/ActivePopupMFTMessageStep.cpp $
  *  @author:  Gregg Kirkpatrick
  *  @version: $Revision: #1 $
  *
  *  Last modification: $DateTime: 2015/10/09 15:42:35 $
  *  Last modified by:  $Author: CM $
  *
  *  Implementation of .
  */
#include "app/response_plans/common/src/ProjectDefinition.h"

#if defined ( STEPTYPE_POPUP_MFT_MESSAGE )

#include "core/utilities/src/DebugUtil.h"
#include "core/message/src/CommsMessageSender.h"
#include "core/message/src/MessagePublicationManager.h"
#include "core/message/types/PlanAgentComms_MessageTypes.h"
#include "bus/response_plans/plan_agent/src/SortableActiveStepId.h"
#include "app/response_plans/plan_agent/src/IActivePlanFlow.h"
#include "app/response_plans/plan_agent/src/ActivePlanBulletinBoard.h"
#include "app/response_plans/plan_agent/src/PlanAgentUser.h"
#include "app/response_plans/plan_agent/src/ActivePopupMFTMessageStep.h"
#include "app/response_plans/common/src/StringConstants.h"

#pragma warning ( disable : 4250 )

namespace TA_Base_App
{
    static const unsigned short SEND_POPUP_MESSAGE_TRY_MAX_TIMES = 3;

	ActivePopupMFTMessageStep::ActivePopupMFTMessageStep( const TA_Base_Core::StepDetail& stepDetail,
														const TA_Base_Core::PopupMFTMessageParameters& params,
														IActivePlanFlow& flowControl ) :
		ActiveStep(stepDetail, flowControl),
		m_params(params),
        m_sendPopupMessageTryTimes(0)
	{
        m_commsSender = TA_Base_Core::MessagePublicationManager::getInstance().getCommsMessageSender( TA_Base_Core::PlanAgentComms::Context );
	}

	TA_Base_Core::EActiveStepState ActivePopupMFTMessageStep::executeImpl( void )
	{
        LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugDebug, "Popup MFT Message step %d", m_detail.position );
		TA_Base_Core::EActiveStepState stepState = TA_Base_Core::EXECUTED_ACTIVE_STEP_STATE;

        TA_Base_Core::CurrentPlanStepDetail detail;

        detail.activePlan = m_flowControl.getPlan();
        detail.step = m_detail.position;
        detail.data.popupMFTMessage(m_params);

        TA_Base_Bus::SortableActiveStepId srtStep = detail;

        const int executeStatus = ActivePlanBulletinBoard::instance()->getStepCompletionStatus( srtStep );

        LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugDebug, "[MftMsg] Plan [%lu, %lu] current state is %d", 
            detail.activePlan.plan, detail.activePlan.instance, executeStatus );

        switch (executeStatus)
        {
        case TA_Base_Core::PSCS_SUCCESS:
            m_flowControl.setNextStep(m_params.pendingStep);
            break;
        case TA_Base_Core::PSCS_UNDEFINED:
            // send message
            if ( m_sendPopupMessageTryTimes < SEND_POPUP_MESSAGE_TRY_MAX_TIMES )
            {
                ++m_sendPopupMessageTryTimes;
                sendActiveStepUpdateMessage(detail);
                m_flowControl.setNextStep(m_params.pendingStep);
            }
            else
            {
                m_remark = RemarkNoMftResponse;
                stepState = TA_Base_Core::FAILED_ACTIVE_STEP_STATE;
                m_sendPopupMessageTryTimes = 0;
            }
            break;
        case TA_Base_Core::PSCS_YES_RESPONSE:
            m_sendPopupMessageTryTimes = 0;
            ActivePlanBulletinBoard::instance()->removeStepCompletionStatus( srtStep );
            m_flowControl.setNextStep(m_params.yesStep);
            break;
        case TA_Base_Core::PSCS_NO_RESPONSE:
            m_sendPopupMessageTryTimes = 0;
            ActivePlanBulletinBoard::instance()->removeStepCompletionStatus( srtStep );
            m_flowControl.setNextStep(m_params.noStep);
            break;
        default:
            m_sendPopupMessageTryTimes = 0;
            ActivePlanBulletinBoard::instance()->removeStepCompletionStatus( srtStep );
            m_remark = RemarkInvalidStepParameter;
            stepState = TA_Base_Core::FAILED_ACTIVE_STEP_STATE;
            LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugError, "Result can not be recognized.");
        }

		return stepState;
	}

    ActivePopupMFTMessageStep::~ActivePopupMFTMessageStep()
    {
        if ( NULL != m_commsSender )
        {
            delete m_commsSender;
            m_commsSender = NULL;
        }
    }

    void ActivePopupMFTMessageStep::sendActiveStepUpdateMessage( const TA_Base_Core::CurrentPlanStepDetail& stepDetail )
    {
        if (ActivePlanBulletinBoard::instance()->isControlMode())
        {
            if (NULL != m_commsSender)
            {
                CORBA::Any commsData;
                commsData <<= stepDetail;

                m_commsSender->sendCommsMessage(TA_Base_Core::PlanAgentComms::ActiveStepUpdate, 
                                                PlanAgentUser::getInstance()->getAgentEntityKey(),
                                                commsData,
                                                PlanAgentUser::getInstance()->getAgentSubsystemKey(),
                                                PlanAgentUser::getInstance()->getAgentLocationKey()
                                                );
            }
            else
            {
                LOG_GENERIC(SourceInfo, TA_Base_Core::DebugUtil::DebugError, "Comms Sender is NULL, fail to send active step update message");
            }
        }
    }

} // TA_Base_App


#endif //  STEPTYPE_POPUP_MFT_MESSAGE

