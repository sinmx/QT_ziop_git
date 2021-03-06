#ifndef THIRDPARTYLIBEXCEPTION_H_INCLUDED
#define THIRDPARTYLIBEXCEPTION_H_INCLUDED

/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/app/response_plans/plan_agent/src/ThirdPartyLibException.h $
  *  @author:  Gregg Kirkpatrick
  *  @version: $Revision: #1 $
  *
  *  Last modification: $DateTime: 2015/10/09 15:42:35 $
  *  Last modified by:  $Author: CM $
  *
  *  <description>
  */

#include "core/exceptions/src/TransactiveException.h"

namespace TA_Base_App
{
	class ThirdPartyLibException : public TA_Base_Core::TransactiveException
	{
	public:
		ThirdPartyLibException() throw();
		ThirdPartyLibException(const std::string& msg) throw();
		virtual ~ThirdPartyLibException() throw();
	};
}; // TA_Base_App

#endif // THIRDPARTYLIBEXCEPTION_H_INCLUDED

