/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/app/scada/inspector_panel_prev/src/StatusDialog.h $
  * @author:  Darren Sampson
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2015/10/09 15:42:35 $
  * Last modified by:  $Author: CM $
  * 
  * This class manages the dialog which displays the status tab shown
  * by the inspector panel.
  */

#ifndef STATUSDIALOG_H
#define STATUSDIALOG_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "app/scada/inspector_panel/src/Equipment.h"
#include "app/scada/inspector_panel/src/resource.h"
#include "app/scada/inspector_panel/src/ITabDialog.h"

#include "bus/scada/common_library/src/CommonDefs.h"

namespace TA_Base_App
{
	class CEquipment;

	/////////////////////////////////////////////////////////////////////////////
	// CStatusDialog dialog

	class CStatusDialog : public CDialog, public ITabDialog
	{
	
	public:
		// Construction
		CStatusDialog(CWnd* pParent = NULL);   // standard constructor

		//
		// ITabDialog Implementation
		//
		virtual void setEquipment(CEquipment* equipment);
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
		//{{AFX_DATA(CStatusDialog)
	enum { IDD = IDD_STATUS };
	CEdit	m_statusInfo;
	//}}AFX_DATA


	// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CStatusDialog)
		protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
		//}}AFX_VIRTUAL

	// Implementation
	protected:
        const char * const getQuality( TA_Base_Bus::EQualityStatus quality ) const;

		// Generated message map functions
		//{{AFX_MSG(CStatusDialog)
		virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
		DECLARE_MESSAGE_MAP()

		CEquipment*			m_equipment;
		bool				m_accessAllowed;
	};

	//{{AFX_INSERT_LOCATION}}
	// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
}

#endif // #ifndef STATUSDIALOG_H
