/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI/TA_BASE/transactive/app/response_plans/plan_manager/src/DataPointTestTypeStepParameter.h $
  * @author:  Bart Golab
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2013/09/03 14:11:12 $
  * Last modified by:  $Author: CM $
  *
  * <description>
  *
  **/

#if !defined(AFX_DATAPOINTTESTTYPESTEPPARAMETER_H__EF0E70D4_C0CB_4C2B_B3FC_0C8A82C4D51E__INCLUDED_)
#define AFX_DATAPOINTTESTTYPESTEPPARAMETER_H__EF0E70D4_C0CB_4C2B_B3FC_0C8A82C4D51E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if defined (STEPTYPE_DATA_POINT_CHECK)

#include <string>
#include "core/data_access_interface/PlanAgent/IDL/src/PlanAgentDataCorbaDef.h"
#include "PlanStepParameter.h"


namespace TA_Base_App
{
    /////////////////////////////////////////////////////////////////////////////
    // DataPointTestTypeStepParameter

    class CPlanStepParameterListCtrlModel;
    class DataPointTestTypeStepParameter : public PlanStepParameter
    {
            // Operations
        public:
            DataPointTestTypeStepParameter(PlanStep& parent, std::string name, TA_Base_Core::EDataPointTest testType);
            DataPointTestTypeStepParameter(PlanStep& parent, const DataPointTestTypeStepParameter& parameter);
            DataPointTestTypeStepParameter(const DataPointTestTypeStepParameter& parameter);
            virtual ~DataPointTestTypeStepParameter();

            virtual void addToParameterList(CPlanStepParameterListCtrlModel& listCtrl);

            TA_Base_Core::EDataPointTest    getDataPointTestType() const
            {
                return m_testType;
            }
            void setDataPointTestType(TA_Base_Core::EDataPointTest testType);

        protected:
            //virtual CPlanStepParameterEditDlg* getEditDialog(bool canEdit);

        private:
            DataPointTestTypeStepParameter& operator=(const DataPointTestTypeStepParameter& parameter);


            // Attributes
        private:
            TA_Base_Core::EDataPointTest m_testType;
    };
}

#endif // defined (STEPTYPE_DATA_POINT_CHECK)

#endif // !defined(AFX_DATAPOINTTESTTYPESTEPPARAMETER_H__EF0E70D4_C0CB_4C2B_B3FC_0C8A82C4D51E__INCLUDED_)
