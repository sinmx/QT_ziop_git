/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/bus/interlocking/BooleanDatapointEntityDll/src/BooleanDatapointEntityDll.cpp $
  * @author:  
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2015/10/09 15:42:35 $
  * Last modified by:  $Author: CM $
  * 
  * This is the 'mainline' of the DLL. This is the entry point and is run when the 
  * Interlocking Rule Trigger Editor loads the DLL.
  *
  */
// BooleanDatapointEntityDll.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>

#include "EntityAction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace TA_Base_Bus
{
    static AFX_EXTENSION_MODULE BooleanDatapointEntityDllDLL = { NULL, NULL };

    extern "C" int APIENTRY
    DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
    {
	    // Remove this if you use lpReserved
	    UNREFERENCED_PARAMETER(lpReserved);

	    if (dwReason == DLL_PROCESS_ATTACH)
	    {
		    TRACE0("BOOLEANDATAPOINTENTITYDLL.DLL Initializing!\n");
		    
		    // Extension DLL one-time initialization
		    if (!AfxInitExtensionModule(BooleanDatapointEntityDllDLL, hInstance))
			    return 0;

		    // Insert this DLL into the resource chain
		    // NOTE: If this Extension DLL is being implicitly linked to by
		    //  an MFC Regular DLL (such as an ActiveX Control)
		    //  instead of an MFC application, then you will want to
		    //  remove this line from DllMain and put it in a separate
		    //  function exported from this Extension DLL.  The Regular DLL
		    //  that uses this Extension DLL should then explicitly call that
		    //  function to initialize this Extension DLL.  Otherwise,
		    //  the CDynLinkLibrary object will not be attached to the
		    //  Regular DLL's resource chain, and serious problems will
		    //  result.

		    new CDynLinkLibrary(BooleanDatapointEntityDllDLL);
	    }
	    else if (dwReason == DLL_PROCESS_DETACH)
	    {
		    TRACE0("BOOLEANDATAPOINTENTITYDLL.DLL Terminating!\n");
		    // Terminate the library before destructors are called
		    AfxTermExtensionModule(BooleanDatapointEntityDllDLL);
	    }
	    return 1;   // ok
    }

    /**
      * createEntityAction
      *
      * Creates an IEntityAction object and returns it to the caller. All further
      * communication between the DLL and main application will happen through this interface.
      *
      *
      * @return IEntityAction*		A new object which implements
      *                             the IEntityAction interface.
      *                             NOTE: The caller is responsible for deleting the pointer.
      */
    extern "C" __declspec(dllexport) IEntityAction* createEntityAction()
    {
	    return new EntityAction();
    }

} // namespace
