#ifndef ACTIVESTEP_H_INCLUDED
#define ACTIVESTEP_H_INCLUDED

/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/app/response_plans/plan_agent/src/ActiveStep.h $
  *  @author:  Gregg Kirkpatrick
  *  @version: $Revision: #1 $
  *
  *  Last modification: $DateTime: 2015/10/09 15:42:35 $
  *  Last modified by:  $Author: CM $
  *
  *  <description>
  */

#include "core/data_access_interface/PlanAgent/IDL/src/PlanAgentDataCorbaDef.h"

namespace TA_Base_App
{
    class IActivePlanFlow;

	//Class declaration
	class ActiveStep
	{
	// Public methods
	public:
        ActiveStep( const TA_Base_Core::StepDetail& detail, IActivePlanFlow& flowControl );
        virtual ~ActiveStep();

		/**
		  * load
		  *
		  * Provided publicly for the specific case where
		  * an object outside the step wishes to force the
		  * step to publish it's state before execute is
		  * called.
		  *
		  */
		void load( bool fUpdateBulletinBoard = true );

		/**
		  * execute
		  *
		  * Allow a client to execute any step in a uniform manner
		  *
		  */
		void execute();
		
		/**
		  * getStepNumber
		  *
		  * each step must know it's own number
		  *
		  */
		TA_Base_Core::StepNumber getStepNumber( void ) const;
        TA_Base_Core::StepId getStepId(void) const;

        bool shouldIgnoreFailure() { return m_detail.ignoreFailure; }
        bool shouldNowait() { return m_detail.nowait; }

        void processStepExecutionFailure( const std::string& failureReson = "" );

		/**
		  * customise
		  *
		  * change a step's customisable behaviour
		  * (e.g. skip, delay)
		  *
		  */
		void customise( const TA_Base_Core::StepCustomisableDetail& newDetail );

	protected:
		/**
		  * executeImpl
		  *
		  * where the work is done.`
		  *
		  */
		virtual TA_Base_Core::EActiveStepState executeImpl( void ) = 0;        

		std::string dumpContext( void ) const;

    protected:
        std::string m_remark;

		TA_Base_Core::StepDetail m_detail;

        bool m_bGroupStep;
        bool m_bSubStep;
		
		ActiveStep& operator=( const ActiveStep& );
		ActiveStep( const ActiveStep& );

		IActivePlanFlow& m_flowControl;

        // Time that the delay started.
        time_t m_delayStartTime;

        // Amount of the delay completed. (Need to keep track of this in case the step is paused
        // in the middle of a delay.)
        time_t m_delayCompleted;
	}; // ActiveStep
}; // TA_Base_App

#endif // ACTIVESTEP_H_INCLUDED
