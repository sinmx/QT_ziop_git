/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/app/scheduling/scheduling_manager/src/MainFrm.h $
  * @author:  
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2015/10/09 15:42:35 $
  * Last modified by:  $Author: CM $
  * 
  * The main frame.  This class is responsible for updating the toolbar base on rights and job selection.
  */

#if !defined(AFX_MAINFRM_H__8FF8DE95_4565_4123_860A_1F8475DC763D__INCLUDED_)
#define AFX_MAINFRM_H__8FF8DE95_4565_4123_860A_1F8475DC763D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "app/scheduling/scheduling_manager/src/SchedulingManagerConstants.h"
#include "app/scheduling/scheduling_manager/plugin/model/src/Job.h"
#include "app/scheduling/scheduling_manager/src/SchedulingManagerView.h"
#include "app/scheduling/scheduling_manager/plugin/model/src/IJobUpdatable.h"
#include "bus/generic_gui_view/src/TransActiveFrame.h"

//TD16358++
//#include "bus/generic_gui_entity/src/ISystemStateUpdateObserver.h"
//++TD16358

namespace TA_Base_App
{
    class CMainFrame : public TA_Base_Bus::AbstractTransActiveFrame,
		public IJobUpdatable
    {
	    
    // Operations
    public:
		CMainFrame(TA_Base_Bus::ITransActiveWinApp * pApp);
		void initJob();
    // Overrides
	    // ClassWizard generated virtual function overrides
	    //{{AFX_VIRTUAL(CMainFrame)
	    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	    //}}AFX_VIRTUAL
		virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

    // Implementation
    public:
	    virtual ~CMainFrame();

        /** 
          * cleanUp
          *
          * Perform any clean up if necessary
          *
          */
        void cleanUp();

		virtual std::string getMyPModelName();
		void setupPModel(void);

		virtual void notifyUpdate(const char * updateType, TA_Base_Bus::EventArgs * args=NULL);

		//////////////////////////////////////////////////////////////////////////////////
        //
        //
        // Methods inherited from IJobUpdatable
        //
        //
        //////////////////////////////////////////////////////////////////////////////////

        /** 
          * updateJobs
          *
          * Calls by the JobManager to update the job list whenever there is a job update.
          *
          */
	    virtual void updateJobs();


        /** 
          * createJob
          *
          * Displays the job dialog for creating a job.
          *
          * @param job The job object that contains the preliminary data to be displayed on the dialog.
          */
	    virtual void createJob(const Job& job);


        /** 
          * updateRights
          *
          * Update the operator privileges on the selected job.
          *
          */
	    virtual void updateRights();


        /** 
          * jobDeleted
          *
          * This is called when a job has been removed from the job list.  
          *
          * @param job The job that has been removed.  
          * @param isAssociatedWithSessionProfiles True if the job is associated with profiles available to this session
          */
        virtual void jobDeleted(const Job& job, const bool isAssociatedWithSessionProfiles);


        /** 
          * jobUpdated
          *
          * This is called when a job has been updated in the job list.  
          *
          * @param job The job that has updated
          * @param isAssociatedWithSessionProfiles True if the job is associated with profiles available to this session
          */
        virtual void jobUpdated(const Job& job, const bool isAssociatedWithSessionProfiles);


    #ifdef _DEBUG
	    virtual void AssertValid() const;
	    virtual void Dump(CDumpContext& dc) const;
    #endif

    protected: // create from serialization only
		CMainFrame();
		DECLARE_DYNCREATE(CMainFrame)
			
			
    protected:  // control bar embedded members
	    CStatusBar  m_wndStatusBar;
	    CToolBar    m_wndToolBar;
		CSchedulingManagerView m_wndSchedulingView;

    // Generated message map functions
    protected:
	    //{{AFX_MSG(CMainFrame)
	    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	    afx_msg void onUpdateJobAdd(CCmdUI* pCmdUI);
	    afx_msg void onUpdateJobDelete(CCmdUI* pCmdUI);
	    afx_msg void onUpdateJobDisable(CCmdUI* pCmdUI);
	    afx_msg void onUpdateJobEdit(CCmdUI* pCmdUI);
	    afx_msg void onUpdateJobEnable(CCmdUI* pCmdUI);
	    afx_msg void onUpdateFilePrint(CCmdUI* pCmdUI);
	    afx_msg void onUpdateViewJobdetails(CCmdUI* pCmdUI);
	    afx_msg void onFilePrint();
		afx_msg LRESULT onSetMessageString(WPARAM wParam, LPARAM lParam);
	    //}}AFX_MSG
        afx_msg LRESULT onJobSelectionChange(WPARAM theJob, LPARAM);
        afx_msg LRESULT onRightsAgentDied(WPARAM, LPARAM);
        afx_msg LRESULT onStatusTextChange(WPARAM text, LPARAM);
        afx_msg LRESULT cleanUp(WPARAM, LPARAM);
		//TD16358++
		afx_msg LRESULT onSystemInNormalMode(WPARAM, LPARAM);
		afx_msg LRESULT onSystemInDegradedMode(WPARAM, LPARAM);
		//++TD16358
		afx_msg LRESULT OnSetLanguage(WPARAM wParam, LPARAM lParam);
	    DECLARE_MESSAGE_MAP()

		void  initUIControl();

    private:
        int initialiseToolbar();

        /**
         * addButton
         *
         * This will add a button to the toolbar.
         * Copied from ConfigurationEditor.
         *
         * @param const CString& This is the name of the button and will be displayed under the icon
         * @param unsigned long The resource id for the button's hot icon
         * @param int The command id for this button.
         */
        void addButton(const CString& buttonName, const unsigned long iconId, const int command);

        /**
	     * CreateGreyscaleIcon()
	     *
	     * This function will greate a grey version of the hot icon passed in automatically.
         * Copied from ConfigurationEditor.
         * 
         * @param HICON A coloured icon to convert to grey-scale
         *
         * @return HICON A grey-scale icon matching the passed-in hot icon. If an error
         *               occurs this will be NULL.
	     */
        HICON createGreyscaleIcon(HICON colourIcon);
        
		//add from doc
		void initialise();

        // Holds icons for when the toolbar buttons are hot (ie the user has their mouse over them)
        CImageList m_toolbarImageListHot;       
                                            
        // Holds the icons for when the toolbar buttons are enabled (ie the button is accessible but
        // the user does not have their mouse over it.
        CImageList m_toolbarImageListEnabled;   

        // Maintains the information required to create and display a button
        struct ButtonInfo
        {
            TA_Base_App::SchedulingManager::EAction action;  // The action associated with this button for determining rights
            char* name;             // Button name
            unsigned long iconId;   // Resource Id for the icon
            int command;            // The command associated with the button
            bool enable;            // Caches the enabling condition so that we don't have to recalculate it each time the 
                                    // update command is called
        };

        // An array which stores the information required to display and control the toolbar buttons
        static ButtonInfo BUTTON_INFO[];

        // The index of the first button
        static const int FIRST_BUTTON_INDEX;

        // The number of buttons on the toolbar
        static const int NUM_BUTTONS;

        // The size in pixels of each button
        static const CSize BUTTON_SIZE;

        // The size in pixels of each image
        static const CSize IMAGE_SIZE;

        // Temporarily cache the selected jobs so that we don't need to determine the rights to the 
        // jobs when the selected jobs are the same
        JobPtrVector* m_lastSelectedJobs;

		CString m_statusBarString;
		
		//TD16358++
		bool bGroupOffline;
		//++TD16358

		JobManager* m_jobManager;

		MainFrameModel* m_pMainFrmModel;
    };
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__8FF8DE95_4565_4123_860A_1F8475DC763D__INCLUDED_)
    