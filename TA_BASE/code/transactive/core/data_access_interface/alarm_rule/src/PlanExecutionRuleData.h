/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/core/data_access_interface/alarm_rule/src/PlanExecutionRuleData.h $
  * @author:  Dirk McCormick
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2015/10/09 15:42:35 $
  * Last modified by:  $Author: CM $
  *
  * PlanExecutionRuleData is an implementation of IPlanExecutionRuleData.
  */

#ifndef PLAN_EXECUTION_RULE_DATA_H
#define PLAN_EXECUTION_RULE_DATA_H

#include "core/data_access_interface/alarm_rule/src/AlarmRuleData.h"
#include "core/data_access_interface/alarm_rule/src/PlanExecutionRuleHelper.h"

namespace TA_Base_Core
{
    class PlanExecutionRuleData : public AlarmRuleData
    {

    public:

        // The string representing this rule type
        static const std::string RULE_TYPE;


        /**
         * Destructor
         */
        virtual ~PlanExecutionRuleData();


        /**
         * Constructor
         *
         * Construct an Alarm Rule class based around a key, this will read
		 * the data from the database and throw a DatabaseException
		 * if not successful
         *
         * @param key The key of this Alarm Rule in the database
         */
        PlanExecutionRuleData( const unsigned long key );

        
        /**
         * Constructor
         *
         * Construct a new alarm rule.
         *
         * @param entityTypeKey  The key of the entity's type.
         * @param entityKey      The entity's key.
         * @param alarmType      The key of the alarm type.
         * @param ruleTrigger    The trigger for this alarm rule.
         * @param planPath       The full path of the plan this rule runs.
         */
        PlanExecutionRuleData(
            unsigned long entityTypeKey,
            unsigned long entityKey,
            unsigned long alarmTypeKey,
            const std::string& ruleTrigger,
            const std::string& planPath);


        /** 
          * PlanExecutionRuleData
          *
          * Constructs a new plan execution rule with blank fields.
          *
          */
        PlanExecutionRuleData();



        /** 
          * PlanExecutionRuleData
          *
          * Creates a copy of the given Alarm Rule
          *
          * @param theRule  the rule to copy
          */
        PlanExecutionRuleData(const PlanExecutionRuleData& theRule);


        /**
         *  Prepends the RULE_TYPE to the getName method of the parent class.
         */
        virtual std::string getName();

            
        /** 
          * getPlanPath
          *
          * Gets the path of the plan in the format "[/<category1>/<categoryN>]/<planName>".
          *
          * @return the full path of the plan as a string.
          *
          */
        virtual std::string getPlanPath();


        /** 
          * setPlanPath
          *
          * Sets the path of the plan.
          *
          * @param planPath  the full path of the plan as a string.
          */
        virtual void setPlanPath(const std::string& planPath);


private:
        // Unused methods
		PlanExecutionRuleData& operator=(const PlanExecutionRuleData&);


        // The plan name parameter.
        static const std::string PLAN_NAME;

    };
} // closes TA_Base_Core

#endif // PLAN_EXECUTION_RULE_DATA_H
