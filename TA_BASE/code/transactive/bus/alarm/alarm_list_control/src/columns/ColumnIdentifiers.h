/**
 * The source code in this file is the property of 
 * Ripple Systems and is not for redistribution
 * in any form.
 *
 * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/bus/alarm/alarm_list_control/src/columns/ColumnIdentifiers.h $
 * @author:  Karen Graham
 * @version: $Revision: #2 $
 *
 * Last modification: $DateTime: 2016/05/11 17:52:04 $
 * Last modified by:  $Author: Noel $
 * 
 * This file should be updated whenever a new alarm action is added so it is easy to tell which resource
 * to use and which ones are free
 */

#ifndef COLUMN_IDENTIFIERS_H
#define COLUMN_IDENTIFIERS_H

namespace TA_Base_Bus
{
    static const long COL_DESCRIPTION          = 1;
	static const long COL_ACK                  = 2;
    static const long COL_STATE                = 3;
    static const long COL_TYPE                 = 4;
    static const long COL_LOCATIONS            = 5;
    static const long COL_COMMENTS             = 6;
    static const long COL_SOURCETIMESTAMP      = 7;
    static const long COL_VALUE                = 9;
    static const long COL_ENTITY               =10;
    static const long COL_TRANSACTIVETIMESTAMP =11;
	static const long COL_SEVERITY             =12;
    static const long COL_SUBSYSTEM            =13;
    static const long COL_DSS                  =14;
    static const long COL_AVL                  =15;
    static const long COL_MMS                  =16;
    static const long COL_ACKTIME              =17;
    static const long COL_ACKNOWLEDGEDBY       =18;
    static const long COL_CLOSETIME            =19;
    static const long COL_ASSET                =20;
	static const long COL_OPERATORTYPE         =21;

    //static const std::string DATE_TIME_FORMAT = "%d/%m/%Y %H:%M:%S"; //TD12474 
};

#endif //COLUMN_IDENTIFIERS_H
