/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/app/system_control/system_manager/src/ShutdownSystemControllerDlg.h $
  * @author:  Dominique Beauregard
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * ShutdownSystemControllerDlg is associated with the dialog box 
  * allowing operators to shutdown the System Controller currently
  * logged into.
  *
  */

#if !defined(AFX_SHUTDOWNSYSTEMCONTROLLERDLG_H__CA6BD944_2D8D_11D5_B140_0050BAB0C7E8__INCLUDED_)
#define AFX_SHUTDOWNSYSTEMCONTROLLERDLG_H__CA6BD944_2D8D_11D5_B140_0050BAB0C7E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bus/generic_gui_view/src/TransActiveDialog.h"

namespace TA_Base_App
{
    class ShutdownSystemControllerDlgModel;

    class ShutdownSystemControllerDlg : public TA_Base_Bus::AbstractDialog
    {

    public:
        ShutdownSystemControllerDlg(TA_Base_Bus::ITransActiveWinApp * app, const std::string & hostname, CWnd* pParent = NULL);
 
        // Dialog Data
	    //{{AFX_DATA(ShutdownSystemControllerDlg)
	    enum { IDD = IDD_SHUTDOWN_MONITOR_DIALOG };
	    CButton	m_shutdownButton;
	    CStatic	m_hostnameLabel;
	    //}}AFX_DATA

        // Overrides
	    // ClassWizard generated virtual function overrides
	    //{{AFX_VIRTUAL(ShutdownSystemControllerDlg)
	    protected:
	    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	    //}}AFX_VIRTUAL

	protected:
        virtual std::string getMyPModelName();
        void setupPModel();

    protected:

	    // Generated message map functions
	    //{{AFX_MSG(ShutdownSystemControllerDlg)

        void initUIControl();
        virtual void OnOK();

		//}}AFX_MSG
	    DECLARE_MESSAGE_MAP()
    private:
        ShutdownSystemControllerDlgModel * m_realPModel;
        std::string m_hostname;
    };

} // namespace TA_Base_App

#endif // !defined(AFX_SHUTDOWNSYSTEMCONTROLLERDLG_H__CA6BD944_2D8D_11D5_B140_0050BAB0C7E8__INCLUDED_)
