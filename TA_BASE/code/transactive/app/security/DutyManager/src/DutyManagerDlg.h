#if !defined(AFX_DUTYMANAGERDLG_H__2146B198_0486_4E14_BD4A_EDBAFDF01ABB__INCLUDED_)
#define AFX_DUTYMANAGERDLG_H__2146B198_0486_4E14_BD4A_EDBAFDF01ABB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI/TA_BASE/transactive/app/security/DutyManager/src/DutyManagerDlg.h $
  * @author:  Bart Golab
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2013/09/03 14:11:12 $
  * Last modified by:  $Author: CM $
  *
  * This class represents the main Rights Manager dialog window.
  *
  */

//#include "DutyManager.h"
#include "bus/generic_gui_view/src/TransActiveDialog.h"

#include "app/security/DutyManager/src/RegionDutyPropertyPage.h"
#include "app/security/DutyManager/src/SubsystemDutyPropertyPage.h"
#include "app/security/DutyManager/src/OtherSesSubDutyPropertyPage.h"

namespace TA_Base_App
{
	class DutyManagerDlgModel;
	//TD18095, replace inheritate from ISessionObserver, and IConfigDataObserver with aggregate two objects.
	class DutyManagerDlg : public TA_Base_Bus::AbstractTransActiveDialog
						   //public TA_Base_Core::SpecialisedMessageSubscriber<TA_Base_Core::CommsMessageCorbaDef>/*,
                          // public TA_Base_Bus::ISessionObserver,
                          // public TA_Base_Bus::IConfigDataObserver//*/
    {
    // Operations
    public:
	    DutyManagerDlg(TA_Base_Bus::ITransActiveWinApp * app, CWnd* pParent = NULL);   // standard constructor
        virtual ~DutyManagerDlg();

		void init();

		//jinhua++
		SubsystemDutyPropertyPage& getSubsytemDutyPropertyPage();
		OtherSesSubDutyPropertyPage& getOhterSesSubDutyPropertyPage();

        /**
        * TA_Base_Core::SpecialisedMessageSubscriber interface
        *
        */
        //virtual void receiveSpecialisedMessage(const TA_Base_Core::CommsMessageCorbaDef& message);



		bool isShowOhterSession()
		{
			return m_showOtherSession;
		}


		//++++++++++++++
		void notifyUpdate(const char * updateType, TA_Base_Bus::EventArgs * args);
		void requestUserReply(TA_Base_Bus::UIReplyEventArgsPtr uiEvent) ;

    private:
        DutyManagerDlg(const DutyManagerDlg& dutyManagerDlg);
        DutyManagerDlg& operator=(const DutyManagerDlg& dutyManagerDlg);


    // Overrides
	    //{{AFX_VIRTUAL(DutyManagerDlg)
	protected:
	    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	    //}}AFX_VIRTUAL

	// Implementation
    protected:
	    // Generated message map functions
	    //{{AFX_MSG(DutyManagerDlg)
	    virtual BOOL OnInitDialog();
        afx_msg void OnAppAbout();
	    afx_msg void OnPaint();
	    afx_msg HCURSOR OnQueryDragIcon();
	    afx_msg void OnSize(UINT nType, int cx, int cy);
		//afx_msg	 void OnTimer(UINT nIDEvent);  //TD17082
		afx_msg void OnAppExit();
		afx_msg void OnClose();
		afx_msg void OnTransActiveHelp();
		afx_msg LRESULT OnReceiveDutyAgentRecover(WPARAM wParam, LPARAM lParam);
		afx_msg LRESULT OnRegionDutyUpdate(WPARAM wParam, LPARAM lParam);
		afx_msg LRESULT OnSubsystemDutyUpdate(WPARAM wParam, LPARAM lParam);
		afx_msg LRESULT OnSessionUpdate(WPARAM wParam, LPARAM lParam);
		afx_msg LRESULT OnPopulateData(WPARAM wParam, LPARAM lParam);

		afx_msg LRESULT OnSetLanguage(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	    DECLARE_MESSAGE_MAP()

		void initUIControl(); // OnInitDialog();

		virtual std::string getMyPModelName();
		void setupPModel();

		void onInitGenericGUICompleted();



    // Dialog data
    private:
	    //{{AFX_DATA(DutyManagerDlg)
	
	//}}AFX_DATA

        void positionControls();  //TD17082

	    HICON m_hIcon;

        //std::string m_originalTitleText; TD18095, jianghp

		//DutyManagerBridge * m_bridge;

        DutyManagerPropertySheet m_dutyPropertySheet;
        RegionDutyPropertyPage *m_regionDutyPropertyPage;
        SubsystemDutyPropertyPage *m_subsystemDutyPropertyPage;
		OtherSesSubDutyPropertyPage *m_otherSesSubDutyPropertyPage;

		bool m_shownStatus;

		//std::string m_showOtherSessionSt;
		bool m_showOtherSession;

	public:
		enum { IDD = IDD_DUTY_MANAGER_DLG };

	
		static bool m_isMartixDataInited;
	private:
		DutyManagerDlgModel * m_realPModel;
    };

} // namespace TA_Base_App

#endif // !defined(AFX_DUTYMANAGERDLG_H__2146B198_0486_4E14_BD4A_EDBAFDF01ABB__INCLUDED_)
