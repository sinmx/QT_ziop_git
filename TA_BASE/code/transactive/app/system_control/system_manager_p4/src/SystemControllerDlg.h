/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/app/system_control/system_manager/src/SystemControllerDlg.h $
  * @author:  Karen Graham
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  * 
  * This is the dialog used to allow the user to enter the System Controller host name and
  * port number.
  */

#if !defined(AFX_SYSTEMCONTROLLERDLG_H__54994F59_29DF_4CB4_9708_38E805786495__INCLUDED_)
#define AFX_SYSTEMCONTROLLERDLG_H__54994F59_29DF_4CB4_9708_38E805786495__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bus/generic_gui_view/src/TransActiveDialog.h"

#include <string>
#include "resource.h"



namespace TA_Base_App
{
	class SystemControllerDlgModel;

    class SystemControllerDlg : public TA_Base_Bus::AbstractDialog
    {
    public:
        /**
          * Constructor
          */
	    SystemControllerDlg(TA_Base_Bus::ITransActiveWinApp * app, CWnd* pParent = NULL);   // standard constructor

        /**
          * Destructor
          */
        virtual ~SystemControllerDlg(){ };



    // Dialog Data
	    //{{AFX_DATA(SystemControllerDlg)
		enum { IDD = IDD_SYSTEMCONTROLLER_DIALOG };
		CEdit	m_hostnameEdit;
	    CEdit	m_portNumber;
	    CComboBox	m_hostnameCombo;
	//}}AFX_DATA


    // Overrides
	    // ClassWizard generated virtual function overrides
	    //{{AFX_VIRTUAL(SystemControllerDlg)
	    protected:
	    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	    //}}AFX_VIRTUAL

    // Implementation
    protected:
    	HICON m_hIcon;

	    // Generated message map functions
	    //{{AFX_MSG(SystemControllerDlg)
	    afx_msg void onOK();

        void initUIControl();
        afx_msg void onChangePortNumber();
		afx_msg void OnSelectHostName();
		afx_msg void OnChangeHostNameEdit();
	afx_msg void OnDropdownHostName();

	//}}AFX_MSG
	    DECLARE_MESSAGE_MAP()

	protected:
        virtual std::string getMyPModelName();
        void setupPModel();
    private:

        /**
         * refresh
         *
         * This checks the status of the controls and enables or disables the OK button.
         */
        void refresh();

		/**
		 * populateHostnamesCombo
		 *
		 * This populates the hostname combobox with host from the database
		 */
		void populateHostnamesCombo();

		SystemControllerDlgModel * m_realPModel;

    };

    //{{AFX_INSERT_LOCATION}}
    // Microsoft Visual C++ will insert additional declarations immediately before the previous line.
}

#endif // !defined(AFX_SYSTEMCONTROLLERDLG_H__54994F59_29DF_4CB4_9708_38E805786495__INCLUDED_)
