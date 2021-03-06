/**
 * The source code in this file is the property of 
 * Ripple Systems and is not for redistribution
 * in any form.
 *
 * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/bus/alarm/alarm_list_control/src/columns/ColumnDecisionSupport.h $
 * @author:  Karen Graham
 * @version: $Revision: #3 $
 *
 * Last modification: $DateTime: 2016/11/22 14:12:39 $
 * Last modified by:  $Author: Noel $
 * 
 * This class provides all the information for the decision support column.
 */

#if !defined(AFX_ColumnDecisionSupport_H__26C75118_4AC8_4594_BBE3_266FC53666A0__INCLUDED_)
#define AFX_ColumnDecisionSupport_H__26C75118_4AC8_4594_BBE3_266FC53666A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bus/alarm/alarm_list_control/src/columns/AbstractAlarmColumn.h"
#include "bus/alarm/alarm_list_control/src/columns/ColumnIdentifiers.h"

namespace TA_Base_Bus
{

    class ColumnDecisionSupport : public AbstractAlarmColumn
	{
		Q_DECLARE_TR_FUNCTIONS(ColumnDecisionSupport)
	public:

        
        /**
         * Constructor
         *
         * @param int - The width of the column
         * @param bool - Whether the column is currently enabled
         * @param Sort* - The ascending sort for the column. If the sort is NULL then the default sort will be used
         * @param Sort* - The descending sort for the column. If the sort is NULL then the default sort will be used
         * @param IAlarmAction* - The action to perform when the user double-clicks on the column. This can be NULL
         *                        signifying no action.
         */
        ColumnDecisionSupport(int width,
                         bool isEnabled,
                         SORT_COLUMN sortCol,
                         IAlarmAction* doubleClickAction);


        virtual ~ColumnDecisionSupport()
        {
        };


        /**
         * getColumnIdentifier
         *
         * @return long - A unique identifier for this column. This is defined in the file ColumnIdentifiers.h
         */
        virtual long getColumnIdentifier() const
        {
            return COL_DSS;
        }


        /**
         * getColumnHeaderText
         *
         * @return std::string - Returns the column header text
         */
		virtual TAUtfString getColumnHeaderText() const
        {
			return tr("P");
        }


        /**
         * getItemText
         *
         * @param AlarmDetailCorbaDef* - The alarm to retrieve information for
         * @param DatabaseCache - This object can be used to retrieve database information if necessary
         *
         * @return std::string - This returns the text to display in the column for the specified alarm.
         */
		virtual const TAUtfString getItemText(unsigned long ulIndex);

    private:
        /**
         * operator= - Hidden as not used
         */
        ColumnDecisionSupport& operator=(const ColumnDecisionSupport& rhs);

        /**
         * Copy constructor - Hidden as not used
         */
        ColumnDecisionSupport(const ColumnDecisionSupport&);
 
	};
} //End of TA_Base_Bus


#endif // !defined(AFX_ColumnDecisionSupport_H__26C75118_4AC8_4594_BBE3_266FC53666A0__INCLUDED_)
