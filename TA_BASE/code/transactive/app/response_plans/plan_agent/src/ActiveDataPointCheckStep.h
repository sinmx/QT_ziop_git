#if defined ( STEPTYPE_DATA_POINT_CHECK )

#ifndef ACTIVEDATAPOINTCHECKSTEP_H_INCLUDED
#define ACTIVEDATAPOINTCHECKSTEP_H_INCLUDED

/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/app/response_plans/plan_agent/src/ActiveDataPointCheckStep.h $
  *  @author:  Gregg Kirkpatrick
  *  @version: $Revision: #1 $
  *
  *  Last modification: $DateTime: 2015/10/09 15:42:35 $
  *  Last modified by:  $Author: CM $
  *
  *  <description>
  */

#include "core/naming/src/NamedObject.h"
#include "bus/scada/common_library/IDL/src/IDataPointAccessCorbaDef.h"
#include "app/response_plans/plan_agent/src/ActiveStep.h"

namespace TA_Base_App
{
	//Class declaration
	class ActiveDataPointCheckStep : public ActiveStep
	{
	// Public methods
	public:
		ActiveDataPointCheckStep( const TA_Base_Core::StepDetail& stepDetail, const TA_Base_Core::DataPointCheckParameters& params, IActivePlanFlow& flowControl );

	protected:
		virtual TA_Base_Core::EActiveStepState executeImpl( void );

	private:
		ActiveDataPointCheckStep& operator=( const ActiveDataPointCheckStep& );
		ActiveDataPointCheckStep( const ActiveDataPointCheckStep& );

		template<class T> bool test( const T& lhs, const T& rhs, TA_Base_Core::EDataPointTest testType);

        const TA_Base_Core::DataPointCheckParameters m_params;

        TA_Base_Core::NamedObject<TA_Base_Bus::IDataPointAccessCorbaDef,
            TA_Base_Bus::IDataPointAccessCorbaDef_ptr, TA_Base_Bus::IDataPointAccessCorbaDef_var> m_dataPoint;

        unsigned long m_ulDpKey;
	}; // ActiveDataPointCheckStep
}; // TA_Base_App

#endif // ACTIVEDATAPOINTCHECKSTEP_H_INCLUDED


#endif //  STEPTYPE_DATA_POINT_CHECK

