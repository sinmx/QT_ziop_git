//
// The source code in this file is the property of
// Ripple Systems and is not for redistribution
// in any form.
//
// Source:   $File: //depot/PRIV_GenericGUI/TA_BASE/transactive/app/response_plans/plan_manager/src/PlanInstanceMap.h $
// @author:  Bart Golab
// @version: $Revision: #2 $
//
// Last modification: $DateTime: 2016/11/21 13:03:08 $
// Last modified by:  $Author: hoa.le $
//
// <description>

#if !defined(AFX_PLANINSTANCEMAP_H__856EA523_2EB7_42EA_992B_2C5988540A5F__INCLUDED_)
#define AFX_PLANINSTANCEMAP_H__856EA523_2EB7_42EA_992B_2C5988540A5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "boost/shared_ptr.hpp"

#include "core/data_access_interface/PlanAgent/IDL/src/PlanAgentDataCorbaDef.h"
#include "app/response_plans/plan_manager/pmodel/src/SynchronisedMap.h"
#include "app/response_plans/plan_manager/src/PlanManagerCommonDefs.h"
#include "app/response_plans/plan_manager/pmodel/src/PlanManagerConsts.h"


namespace TA_Base_App
{
    class PlanInstance;


    /////////////////////////////////////////////////////////////////////////////
    // PlanStep

    class PlanInstanceMap
    {
    // Operations
    public:
        PlanInstanceMap();
        PlanInstanceMap(const TA_Base_Core::ActivePlanDetails &activePlanDetails);
        virtual ~PlanInstanceMap();

        void addPlanInstances(const TA_Base_Core::ActivePlanDetails &activePlanDetails);
        void getPlanInstances(PlanInstanceList &planInstances);
        PlanInstanceSharedPtr getPlanInstance(const PlanInstanceId &instanceId);
        PlanInstanceSharedPtr getPlanInstance(PlanInstanceNumber instanceNumber, LocationKey locationKey);
        //void updatePlanInstance(const TA_Base_Core::ActivePlanDetail &activePlanDetail);
        //void updatePlanInstance(const TA_Base_Core::PlanCustomisationUpdate &planCustomDetail);

    protected:
        void addPlanInstance(const TA_Base_Core::ActivePlanDetail &activePlanDetail);
        void removePlanInstance(const TA_Base_Core::ActivePlanDetail &activePlanDetail);

    private:
        PlanInstanceMap(const PlanInstanceMap &other);
        PlanInstanceMap &operator=(const PlanInstanceMap &other);


    // Attributes
    private:
        SynchronisedMap<PlanInstanceId, PlanInstanceSharedPtr > m_planInstanceMap;
    };
}

#endif // !defined(AFX_PLANINSTANCEMAP_H__856EA523_2EB7_42EA_992B_2C5988540A5F__INCLUDED_)
