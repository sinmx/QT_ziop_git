/**
  * The source code in this file is the property of 
  * Ripple Systems Pty Ltd and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/core/exceptions/src/PlanControllerException.h $
  * @author J. Ebedes
  * @version $Revision: #1 $
  * Last modification: $DateTime: 2015/10/09 15:42:35 $
  * Last modified by: 
  * 
  * This file outlines a simple exception class for use with
  * the Plan Controller. It is derived from TransActiveException.
  */

#if !defined(AFX_PLANCONTROLLEREXCEPTION_H__44BE1879_4870_11D7_B150_0080C8E32E69__INCLUDED_)
#define AFX_PLANCONTROLLEREXCEPTION_H__44BE1879_4870_11D7_B150_0080C8E32E69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TransactiveException.h"
#include <string>

namespace TA_Base_Core
{
	class PlanControllerException : public TransactiveException  
	{
	public:
		PlanControllerException();
		PlanControllerException(const std::string& msg);
		virtual ~PlanControllerException();

	};
}

#endif // !defined(AFX_PLANCONTROLLEREXCEPTION_H__44BE1879_4870_11D7_B150_0080C8E32E69__INCLUDED_)

