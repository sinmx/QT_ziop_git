/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI/TA_BASE/transactive/app/scada/inspector_panel/src/MeterDialog.h $
  * @author:  Andy Parker
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2013/09/03 14:11:12 $
  * Last modified by:  $Author: CM $
  * 
  * This class manages the dialog which displays the Override tab shown
  * by the inspector panel.
  */

#ifndef METERDIALOG_H
#define METERDIALOG_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "app/scada/inspector_panel/src/MeterListCtrl.h"
#include "app/scada/inspector_panel/src/resource.h"
#include "app/scada/inspector_panel/src/ITabDialog.h"

namespace TA_Base_App
{
	/////////////////////////////////////////////////////////////////////////////
	// CMeterDialog dialog

	class CMeterDialog : public CDialog, public ITabDialog
	{
	
	public:

	// Construction
		CMeterDialog(CWnd* pParent = NULL);   // standard constructor

		//
		// ITabDialog Implementation
		//
		virtual void refreshAllData();
		virtual void updateDataPoint(unsigned long key, TA_Base_Bus::ScadaEntityUpdateType updateType);
		virtual void updateDataNode(TA_Base_Bus::ScadaEntityUpdateType updateType);
		virtual bool isUnsavedChangeOnTab();
		virtual bool isOkToChangeTab();
		virtual void getWindowRect(CRect* rect);
		virtual unsigned int getMinimumHeight();
		virtual void resize(unsigned int height);
		virtual void updatePermissions(/*TA_Base_Bus::RightsLibrary* rightsMgr*/);
		virtual bool isAnyDataPointsDisplayedInTab() const;
		virtual void resetList();

	// Dialog Data
		//{{AFX_DATA(CMeterDialog)
		enum { IDD = IDD_METER };
			// NOTE: the ClassWizard will add data members here
		//}}AFX_DATA


	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(COverrideDialog)
		protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
		virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
		//}}AFX_VIRTUAL

	// Implementation
	protected:

		// Generated message map functions
		//{{AFX_MSG(COverrideDialog)
		virtual BOOL OnInitDialog();		
		//}}AFX_MSG
		DECLARE_MESSAGE_MAP()

		private:

			CMeterListCtrl			m_list;
			unsigned int			m_heightDifference;
			unsigned int			m_originalHeight;
			bool					m_accessAllowed;
	};

	//{{AFX_INSERT_LOCATION}}
	// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
}

#endif // #ifndef METERDIALOG_H
