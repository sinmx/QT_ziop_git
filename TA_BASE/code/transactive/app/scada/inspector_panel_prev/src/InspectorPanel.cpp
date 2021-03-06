/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/app/scada/inspector_panel_prev/src/InspectorPanel.cpp $
  * @author:  Andy Parker
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2015/10/09 15:42:35 $
  * Last modified by:  $Author: CM $
  * 
  * This class provides the base application class for the inspector panel.  It is implemented
  * as a managed process.
  */

#include "app/scada/Inspector_Panel/src/stdafx.h"

#include "app/scada/Inspector_Panel/src/InspectorPanel.h"
#include "app/scada/Inspector_Panel/src/InspectorPanelDlg.h"
#include "app/scada/Inspector_Panel/src/InspectorPanelGUI.h"

#include "core\utilities\src\DebugUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using TA_Base_Bus::TransActiveWinApp;

namespace TA_Base_App
{
	/////////////////////////////////////////////////////////////////////////////
	// CInspectorPanelApp

	BEGIN_MESSAGE_MAP(CInspectorPanelApp, TransActiveWinApp)
		//{{AFX_MSG_MAP(CInspectorPanelApp)
			// NOTE - the ClassWizard will add and remove mapping macros here.
			//    DO NOT EDIT what you see in these blocks of generated code!
		//}}AFX_MSG
	END_MESSAGE_MAP()

	/////////////////////////////////////////////////////////////////////////////
	// CInspectorPanelApp construction

	CInspectorPanelApp::CInspectorPanelApp() : TransActiveWinApp( new InspectorPanelGUI, "Inspector Panel" )
	{
	}

	/////////////////////////////////////////////////////////////////////////////
	// The one and only CInspectorPanelApp object

	CInspectorPanelApp theApp;
}

