/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/bus/mathematical_evaluation/src/RealNumberSquareRootExpression.cpp $
  * @author:  Robert Stagg
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2015/10/09 15:42:35 $
  * Last modified by:  $Author: CM $
  * 
  */

#include <math.h>

#include "bus/mathematical_evaluation/src/RealNumberSquareRootExpression.h"
#include "core/utilities/src/TAAssert.h"

namespace TA_Base_Bus
{
    RealNumberSquareRootExpression::RealNumberSquareRootExpression(std::auto_ptr< IRealNumberExpression > rightHandSide)
    :m_rightHandSide(rightHandSide)
    {
        TA_ASSERT(m_rightHandSide.get() != NULL, "rightHandSide is null!");
    }


    RealNumberSquareRootExpression::~RealNumberSquareRootExpression()
    {
        m_rightHandSide = std::auto_ptr< IRealNumberExpression >(static_cast< IRealNumberExpression* >(NULL));
    }


    double RealNumberSquareRootExpression::evaluate() const
    {
        return sqrt(m_rightHandSide->evaluate());
    }
}
