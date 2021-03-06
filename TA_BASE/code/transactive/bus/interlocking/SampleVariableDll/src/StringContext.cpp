/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/bus/interlocking/SampleVariableDll/src/StringContext.cpp $
  * @author:  Daniel Hoey
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2015/10/09 15:42:35 $
  * Last modified by:  $Author: CM $
  * 
  */

#include "stdafx.h"
#include "StringContext.h"

namespace TA_Base_Bus
{
    /**
    * Constructor
    * 
    */
    StringContext::StringContext()
    {
    }

    /**
    * Destructor
    * 
    */
    StringContext::~StringContext()
    {
    }

    /**
     * getValue
     *
     * Gets the value of a variable.
     *
     * @exception MathematicalEvaluationException - if variable cannot be found
     */
    std::string StringContext::getValue(const std::string& variableName) const
    {
        // TODO add the required code to correctly evaluate this variable
        return variableName;
    }

}
