/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/app/response_plans/plan_manager/src/PlanPathStepParameter.h $
  * @author:  Bart Golab
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2015/10/09 15:42:35 $
  * Last modified by:  $Author: CM $
  *
  * <description>
  *
  **/

#if !defined(AFX_PLANPATHSTEPPARAMETER_H__AE893342_BF8C_43F6_8BEE_94C05F0A9F48__INCLUDED_)
#define AFX_PLANPATHSTEPPARAMETER_H__AE893342_BF8C_43F6_8BEE_94C05F0A9F48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "PlanStepParameter.h"
#include "PlanStepParameterListCtrl.h"
#include "PlanManagerCommonDefs.h"


namespace TA_Base_App
{
    /////////////////////////////////////////////////////////////////////////////
    // PlanPathStepParameter

    class PlanPathStepParameter : public PlanStepParameter
    {
    // Operations
    public:
        PlanPathStepParameter(PlanStep& parent, std::string name, TreeNodeId planNodeId);
        PlanPathStepParameter(PlanStep& parent, PlanPathStepParameter& parameter);
        PlanPathStepParameter(PlanPathStepParameter& parameter);
        virtual ~PlanPathStepParameter();

        virtual void addToParameterList(CPlanStepParameterListCtrl& listCtrl);

        TreeNodeId getPlanNodeId() const { return m_planNodeId; }
        void setPlanNodeId(TreeNodeId planNodeId);
        std::string getPlanPath();

    protected:
        virtual CPlanStepParameterEditDlg* getEditDialog(bool canEdit);

    private:
        PlanPathStepParameter& operator=(const PlanPathStepParameter& parameter);


    // Attributes
    private:
        TreeNodeId m_planNodeId;
    };
}

#endif // !defined(AFX_PLANPATHSTEPPARAMETER_H__AE893342_BF8C_43F6_8BEE_94C05F0A9F48__INCLUDED_)
