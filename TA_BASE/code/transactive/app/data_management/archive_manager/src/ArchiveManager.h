/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/app/data_management/archive_manager/src/ArchiveManager.h $
  * @author:  Alan Brims
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2016/10/18 15:45:45 $
  * Last modified by:  $Author: huirong.luo $
  *
  * User interface for Archive Operations
  *
  */

#if !defined(AFX_ARCHIVEMANAGER_H__13EF9430_909E_4319_9238_94999F357E69__INCLUDED_)
#define AFX_ARCHIVEMANAGER_H__13EF9430_909E_4319_9238_94999F357E69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "bus/generic_gui_view/src/TransActiveWinApp.h"
#include "app/data_management/archive_manager/pmodel/src/ArchiveManagerAppController.h"

namespace TA_Base_App
{

    /////////////////////////////////////////////////////////////////////////////
    // CArchiveManagerApp:
    // See ArchiveManager.cpp for the implementation of this class
    //

    class CArchiveManagerApp : public TA_Base_Bus::TransActiveWinApp
    {
    public:
        /**
          * CArchiveManagerApp
          *
          * Standard constructor.
          */

        CArchiveManagerApp();

        /**
          * ~CArchiveManagerApp
          *
          * Standard destructor.
          */

        virtual ~CArchiveManagerApp() {};
        
        // Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CArchiveManagerApp)
    public:
        //}}AFX_VIRTUAL
        
        // Implementation
        
        //{{AFX_MSG(CArchiveManagerApp)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

		TA_Base_Bus::IApplicationController * createApplicationController();
		CWnd* createMainView(UINT & dlgID);
		void doCommand(const char * commandName, const char * params);
		virtual void prepareAppRun();
            
    private:
        //
        // Disable the copy constructor and assignment operator.
        //

        CArchiveManagerApp( const CArchiveManagerApp& );
        CArchiveManagerApp& operator=( const CArchiveManagerApp& );
    };
    
} // TA_Base_App


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARCHIVEMANAGER_H__13EF9430_909E_4319_9238_94999F357E69__INCLUDED_)