/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/StdAfx.h $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2015/10/09 15:42:35 $
  * Last modified by:  $Author: CM $
  *
  */
// StdAfx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once
#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>       // MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
    #include <afxcmn.h>         // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#pragma warning(disable: 4996 4819 4503 4172)

#include <ace/Future.h>
#include <ace/Singleton.h>
#include <ace/Process.h>
#include <ace/Process_Manager.h>
#include <ace/OS_NS_time.h>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/assign.hpp>
#include <boost/preprocessor.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>
#include <boost/thread/latch.hpp>
#include <boost/thread/barrier.hpp>
#include <boost/thread/executors/basic_thread_pool.hpp>
#include <boost/any.hpp>
#include <boost/utility.hpp>
#include <boost/type_traits.hpp>
#include <boost/format.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/signals2.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <boost/container/map.hpp>
#include <boost/container/vector.hpp>
#include <boost/container/list.hpp>
#include <boost/move/move.hpp>
#include <boost/algorithm/algorithm.hpp>
#include <boost/algorithm/cxx11/one_of.hpp>
#include <boost/algorithm/cxx11/none_of.hpp>
#include <boost/preprocessor/cat.hpp>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <set>
#include <algorithm>
#include <list>
#include <fstream>
