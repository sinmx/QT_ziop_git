/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/app/system_control/system_manager_prev/src/OptionsDlg.cpp $
  * @author:  Dominique Beauregard
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2015/10/09 15:42:35 $
  * Last modified by:  $Author: CM $
  *
  * OptionsDlg is associated with the dialog that allows
  * operators to set the data refresh rate.
  *
  */

#pragma warning(disable:4786)

#include "StdAfx.h"
#include "OptionsDlg.h"
#include "AdminManager.h"

#include <vector>

namespace TA_Base_App
{

    OptionsDlg::OptionsDlg(CWnd* pParent /*=NULL*/)
        : CDialog(OptionsDlg::IDD, pParent)
    {
        //{{AFX_DATA_INIT(OptionsDlg)
            // NOTE: the ClassWizard will add member initialization here
        //}}AFX_DATA_INIT
    }


    void OptionsDlg::DoDataExchange(CDataExchange* pDX)
    {
        CDialog::DoDataExchange(pDX);
        //{{AFX_DATA_MAP(OptionsDlg)
        DDX_Control(pDX, IDC_REFRESH_RATE_COMBO, m_RefreshRate);
        //}}AFX_DATA_MAP
    }


    BEGIN_MESSAGE_MAP(OptionsDlg, CDialog)
        //{{AFX_MSG_MAP(OptionsDlg)
        //}}AFX_MSG_MAP
    END_MESSAGE_MAP()


    BOOL OptionsDlg::OnInitDialog()
    {
        CDialog::OnInitDialog();

        std::vector<int> intervals = AdminManager::getInstance().getRefreshIntervals();
        for (unsigned int i = 0; i < intervals.size(); i++)
        {
            CString tmpString;
            tmpString.Format("%d s", intervals[i]);
            m_RefreshRate.SetItemData(m_RefreshRate.AddString(tmpString),i);
        }
        m_RefreshRate.SetCurSel(AdminManager::getInstance().getCurrentRefreshRate());

        return TRUE;  // return TRUE unless you set the focus to a control
                      // EXCEPTION: OCX Property Pages should return FALSE
    }

    void OptionsDlg::OnOK()
    {
        AdminManager::getInstance().setRefreshRate(m_RefreshRate.GetCurSel());

        CDialog::OnOK();
    }

} // namespace TA_Base_App
