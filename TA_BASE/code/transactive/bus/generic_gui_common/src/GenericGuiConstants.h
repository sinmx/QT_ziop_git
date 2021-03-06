/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/bus/generic_gui_pmod/src/GenericGuiConstants.h $
  * @author:  San Teo
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  * 
  * This file contains the constants required to launch an application
  * 
  */

#if !defined(__GENERIC_GUI_CONSTANTS_H__)
#define __GENERIC_GUI_CONSTANTS_H__

#include "bus/generic_gui_common/src/PModelDataType.h"

// Since this is a constant file that may be used by applications and control station we use
// two levels of namespace to ensure clashes do not happen.
namespace TA_Base_Bus
{
	namespace TA_GenericGui
	{
        ////////////////////////////////////////////////////////////////////////
        // 
        // Enumerated types and constants required for application positioning
        //
        ////////////////////////////////////////////////////////////////////////

        /// Used to specify a screen on the MFT
        enum EScreen                
        {
            SCREEN_CURRENT,         ///<  Area within the current monitor that currentX lies on 
            SCREEN_PREVIOUS,        ///<  Area within the monitor on the left of the one that currentX lies on.  If there is no screen on the left of this, it will just use the current monitor.
            SCREEN_NEXT,            ///<  Area within the monitor on the right of the one that currentX lies on.  If there is no screen on the right of this, it will just use the current monitor.
            SCREEN_SPECIFIC,        ///<  Area within the specified monitor
            SCREEN_FIRST,           ///<  Area within the first monitor (ignores val)
            SCREEN_LAST,            ///<  Area within the last monitor (ignores val)
            SCREEN_ALL              ///<  Area within all screens
        };

        /// Used to specify an area on the screen
        enum EArea                  
        {
            AREA_SCREEN,            ///<  The entire screen area
            AREA_BANNER,            ///<  The banner area
            AREA_LAUNCHPAD,         ///<  The launch pad area 
            AREA_MAINNAVIGATOR,     ///<  The main navigator area
            AREA_SCHEMATIC,         ///<  The display area within the main navigator
        };

        /// Used to indicate how the application will be positioned, can use a combination
        enum EPosition              
        {
            POS_NONE = 0,           ///<  Do not move the window
            POS_RELATIVE = 0x1,     ///<  Relative to the 'objectDim'.  
            POS_BOUNDED = 0x2,      ///<  Bounded within the rectangle area of 'boundaryDim'.
            POS_NOOVERLAP = 0x4,    ///<  Relative to the edges of 'objectDim'
            POS_RESIZABLE = 0x8     ///<  If POS_BOUNDED is defined, it will resize to fit within the boundary
        };

        /// Used to indicate how the application will be aligned relative to a point, can use a combination
        enum EAlignment             
        {
            ALIGN_NONE = 0x0,       ///<  No need to Align
            ALIGN_FIT = 0x1,        ///<  Fit into the specified area
            ALIGN_LEFT = 0x2,       ///<  Leftmost position at x coordinate of 'objectDim' or 'boundaryDim'
            ALIGN_VERTICAL = 0x4,   ///<  Vertically centred (i.e. x coordinate = [left+right]/2)'objectDim' or 'boundaryDim'
            ALIGN_RIGHT = 0x8,      ///<  Rightmost position at x coordinate of 'objectDim' or 'boundaryDim'
            ALIGN_TOP = 0x10,       ///<  Topmost position at y coordinate of 'objectDim' or 'boundaryDim'
            ALIGN_HORIZONTAL = 0x20,///<  Horizontally centred (i.e. y coordinate = [top+bottom]/2) 'objectDim' or 'boundaryDim'
            ALIGN_BOTTOM = 0x40,    ///<  Bottommost position at y coordinate of 'objectDim' or 'boundaryDim'
        };

        /// The new position of the window
        enum EWindowPosition        
        {
            MINIMISE,               ///<  Minimise the app
            MAXIMISE,               ///<  Maximise the app
            FOCUS,                  ///<  Give focus to the app
            REPOSITION,             ///<  Reposition the app
            NO_REPOSITION,          ///<  This is the same as FOCUS but this is used in launchApplication call rather than getFocus call
            CENTRE,                 ///<  Center the app
            REPOSITION_NO_RESTORE
        };

        /// Used to indicate caller has not specified a proper rectangle area
        static const RECT DEFAULT_RECT = {-1, -1, -1, -1};


    };
};

#endif

