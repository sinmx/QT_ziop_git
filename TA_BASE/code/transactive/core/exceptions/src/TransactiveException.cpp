/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/core/exceptions/src/TransactiveException.cpp $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2015/10/09 15:42:35 $
  * Last modified by:  $Author: CM $
  *
  * <description>
  *
  */
#include "TransactiveException.h"

namespace TA_Base_Core
{
    TransactiveException::TransactiveException(const std::string& msg)
        : m_msg(msg)
    {
    }

    const char* TransactiveException::what() const
    {
        return m_msg.c_str();
    }

    UnimplementException::UnimplementException(const std::string& msg)
        : TransactiveException(msg)
    {
    }
}
