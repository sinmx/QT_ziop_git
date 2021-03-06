/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI/TA_BASE/transactive/app/scada/inspector_panel/src/InformationDialog.cpp $
  * @author:  Andy Parker
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2013/09/03 14:11:12 $
  * Last modified by:  $Author: CM $
  * 
  * This class manages the dialog which displays the equiment information tab shown
  * by the inspector panel.  It allows the operator to view the values of the data points.
  */

#include "app/scada/Inspector_Panel/src/stdafx.h"

#include "app/scada/inspector_panel/src/InspectorPanel.h"
#include "app/scada/inspector_panel/src/InformationDialog.h"
#include "core/utilities/src/DebugUtil.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace TA_Base_App
{
	/////////////////////////////////////////////////////////////////////////////
	// CInformationDialog dialog


	CInformationDialog::CInformationDialog(CWnd* pParent /*=NULL*/)
		: CDialog(CInformationDialog::IDD, pParent), m_heightDifference(0), /* m_accessAllowed(false)*/
		  m_originalHeight (0)
	{
		FUNCTION_ENTRY ("CInformationDialog()");

		//{{AFX_DATA_INIT(CInformationDialog)
			// NOTE: the ClassWizard will add member initialization here
		//}}AFX_DATA_INIT

		FUNCTION_EXIT;
	}

	void CInformationDialog::OnShowWindow(BOOL bShow, UINT nStatus) 
	{
		FUNCTION_ENTRY ("OnShowWindow()");

		CDialog::OnShowWindow(bShow, nStatus);

		// TODO: Add your message handler code here

		if (bShow)
		{
			m_informationList.refreshAllData();
		}
		else
		{
			::SendMessage(m_informationList.m_hWnd,WM_KILLFOCUS,0,0);
		}

		FUNCTION_EXIT;
	}

	void CInformationDialog::refreshAllData()
	{
		FUNCTION_ENTRY ("refreshAllData");

		m_informationList.refreshAllData();

		FUNCTION_EXIT;
	}

	void CInformationDialog::DoDataExchange(CDataExchange* pDX)
	{
		FUNCTION_ENTRY ("DoDataExchange()");

		CDialog::DoDataExchange(pDX);
		//{{AFX_DATA_MAP(CInformationDialog)
			// NOTE: the ClassWizard will add DDX and DDV calls here
		//}}AFX_DATA_MAP

		FUNCTION_EXIT;
	}


	BEGIN_MESSAGE_MAP(CInformationDialog, CDialog)
		//{{AFX_MSG_MAP(CInformationDialog)
		//}}AFX_MSG_MAP
		//ON_WM_SHOWWINDOW()
	END_MESSAGE_MAP()

	/////////////////////////////////////////////////////////////////////////////
	// CInformationDialog message handlers

	BOOL CInformationDialog::OnInitDialog() 
	{
		FUNCTION_ENTRY ("OnInitDialog()");

		CDialog::OnInitDialog();

		m_informationList.SubclassDlgItem(IDC_INFO_DATAPOINTLIST,this);

		FUNCTION_EXIT;
		
		return TRUE;  // return TRUE unless you set the focus to a control
					  // EXCEPTION: OCX Property Pages should return FALSE
	}


	void CInformationDialog::updateDataPoint(unsigned long key, TA_Base_Bus::ScadaEntityUpdateType updateType)
	{
		FUNCTION_ENTRY ("updateDataPoints()");

		//m_informationList.updateDataPoint(key, updateType);

		FUNCTION_EXIT;
	}

	void CInformationDialog::updateDataNode(TA_Base_Bus::ScadaEntityUpdateType updateType)
	{
		FUNCTION_ENTRY ("updateDataNode()");

		//m_informationList.updateDataNode(updateType);

		FUNCTION_EXIT;
	}

	bool CInformationDialog::isUnsavedChangeOnTab()
	{
		FUNCTION_ENTRY ("isUnsavedChangeOnTab()");
		FUNCTION_EXIT;

		return false;
	}

	bool CInformationDialog::isOkToChangeTab()
	{
		FUNCTION_ENTRY ("isOkToChangeTab()");
		FUNCTION_EXIT;

		return true;
	}

	void CInformationDialog::getWindowRect(CRect* rect)
	{
		GetWindowRect(rect);
	}

	unsigned int CInformationDialog::getMinimumHeight()
	{
		if (m_heightDifference == 0)
		{
			CRect listRect, dialogRect;
			m_informationList.GetWindowRect(&listRect);
			GetWindowRect(&dialogRect);

			listRect.NormalizeRect();
			dialogRect.NormalizeRect();

			m_heightDifference = dialogRect.Height() - listRect.Height();
		}

		if (m_originalHeight == 0)
		{
			CRect dialogRect;
			GetWindowRect(&dialogRect);
			dialogRect.NormalizeRect();

			m_originalHeight = dialogRect.Height();
		}

		unsigned int nItem = m_informationList.GetItemCount();
		unsigned int height = m_heightDifference;

		if (nItem > 0)
		{
			if (nItem > 20)
			{
				nItem = 20;
			}

			CRect cellRect;
			m_informationList.GetSubItemRect(0, 0, LVIR_LABEL, cellRect);

			cellRect.NormalizeRect();

//			height += cellRect.Height()*(nItem+3);
			height += cellRect.Height()*(nItem+1)+9; // remove half line
		}
		else
		{
			height = m_originalHeight;
		}

		return height;
	}		

	void CInformationDialog::resize(unsigned int height)
	{
		CRect listRect, dialogRect;
		m_informationList.GetWindowRect(&listRect);
		GetWindowRect(&dialogRect);

		listRect.NormalizeRect();
		dialogRect.NormalizeRect();

		int diff = height - dialogRect.Height();
		if(diff == 0)
		{
			return;
		}

		if (diff > 0)
		{
			listRect.InflateRect(0, 0, 0, diff);
			dialogRect.InflateRect(0, 0, 0, diff);
		}
		else
		{
			listRect.DeflateRect(0, 0, 0, -diff);
			dialogRect.DeflateRect(0, 0, 0, -diff);
		}

		m_informationList.SetWindowPos(NULL, 0, 0, listRect.Width(), listRect.Height(), SWP_NOMOVE|SWP_NOZORDER);
		SetWindowPos(NULL, 0, 0, dialogRect.Width(), dialogRect.Height(), SWP_NOMOVE|SWP_NOZORDER);
	}

	void CInformationDialog::updatePermissions(/*TA_Base_Bus::RightsLibrary* rightsMgr*/)
	{

	}

	LRESULT CInformationDialog::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
	{				
		if ((message == WM_COMMAND) && ((wParam == IDOK) || (wParam == IDCANCEL)))
		{
			return 0;
		} else
			return CDialog::WindowProc(message, wParam, lParam);
	}

	bool CInformationDialog::isAnyDataPointsDisplayedInTab() const
	{
		return m_informationList.isAnyDataPointsDisplayedOnScreen();
	}

	void CInformationDialog::resetList()
	{
		m_informationList.resetList();
	}

}


