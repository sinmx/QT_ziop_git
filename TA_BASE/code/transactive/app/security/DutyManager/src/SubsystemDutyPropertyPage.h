#if !defined(AFX_SUBSYSTEMDUTYPROPERTYPAGE_H__2DD28A53_0AA4_4153_9C2F_8004F3884A5B__INCLUDED_)
#define AFX_SUBSYSTEMDUTYPROPERTYPAGE_H__2DD28A53_0AA4_4153_9C2F_8004F3884A5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI/TA_BASE/transactive/app/security/DutyManager/src/SubsystemDutyPropertyPage.h $
  * @author:  Bart Golab
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2013/09/03 14:11:12 $
  * Last modified by:  $Author: CM $
  *
  * This class represents the "Subsystems" tab. It displays the active 
  * subsystem duty state for every physical subsystem in every region.
  *
  */

#include "bus/generic_gui_view/src/TransActivePropertySheet.h"
//TD15533++
#include "bus/mfc_extensions/src/grid_control/GridCtrlS.h"
//++TD15533

namespace TA_Base_App
{
	class SubsystemDutyPropertyPageModel;

    class SubsystemDutyPropertyPage : public AbstractPropertyPage
    {
	    //DECLARE_DYNCREATE(SubsystemDutyPropertyPage)

    // Operations
    public:
	    SubsystemDutyPropertyPage(ITransActiveWinApp * pWinApp, UINT nIDTemplate, UINT nIDCaption = 0 );
	    virtual ~SubsystemDutyPropertyPage();

		//+++++++++++++++++++++
		virtual std::string getMyPModelName();
		virtual void setupPModel();
		 virtual void initUIControl();
		//+++++++++++++++++++++++
		TA_Base_Bus::DataCache&				getDataCache();	
		TA_Base_Bus::SessionCache&			getSessionCashe();
		TA_Base_Bus::SubsystemDutyMatrix&	getSubsystemDutyMatrix();
		TA_Base_Bus::SessionInfoEx  getCurrentSessionInfo();
		TA_Base_Bus::ProfileKeyList getPreviousProfileId();

		// DutyRights
		bool canTransferSubsystems(long lActionId);

		std::string							getRegionDisplayName(RegionKey key);
		std::string							getRegionName(RegionKey key);
		virtual void notifyUpdate(const char * updateType, TA_Base_Bus::EventArgs * args=NULL);
		virtual void requestUserReply(TA_Base_Bus::UIReplyEventArgsPtr uiEvent);


        //TD17082++ made public to allow the client handle the initialization call
		void initialiseSubsystemDutyGrid();

		void initialiseSubsystemDutyGridStatic();

		void updateSubsystemDutyGrid();

		void OnSubsystemDutyUpdate(const SubsystemDutyUpdate& dutyUpdate);
		void OnSessionUpdate(const SessionUpdate& sessionUpdate);
    protected:
        
        void enableDutyControlButtons();
        void addSubsystem(
			TA_Base_Bus::SubsystemKey subsystemKey, 
			TA_Base_Bus::ProfileKeyList profileKeys,
			TA_Base_Bus::RegionKeyList regionKeys); //TD15533
        void removeSubsystem(TA_Base_Bus::SubsystemKey subsystemKey);
        void updateSubsystems(TA_Base_Bus::SubsystemKeyList oldSubsystemKeys, TA_Base_Bus::SubsystemKeyList newSubsystemKeys, TA_Base_Bus::ProfileKeyList profileKeys); //TD15533

    // Overrides
	    // ClassWizard generate virtual function overrides
	    //{{AFX_VIRTUAL(SubsystemDutyPropertyPage)
	protected:
	    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	    //}}AFX_VIRTUAL


    // Implementation
    protected:

	    // Generated message map functions
	    //{{AFX_MSG(SubsystemDutyPropertyPage)
	    virtual BOOL OnInitDialog();
	    afx_msg void OnSize(UINT nType, int cx, int cy);
        //afx_msg LRESULT OnReceiveSessionUpdate(WPARAM wParam, LPARAM lParam);
        //afx_msg LRESULT OnReceiveSubsystemDutyUpdate(WPARAM wParam, LPARAM lParam);
	    afx_msg void OnShowAllSubsystems();
	    afx_msg void OnTransferSubsystemDutyBtn();
	    afx_msg void OnTransferAllSubsystemDutyBtn();
	    //}}AFX_MSG
	    DECLARE_MESSAGE_MAP()


    // Dialog Data
    private:
	    //{{AFX_DATA(SubsystemDutyPropertyPage)
	    enum { IDD = IDD_SUBSYSTEMS_DLG };
	    CButton	m_showAllSubsystemsBtn;
	    CButton	m_transferSubsystemDutyBtn;
	    CButton	m_transferAllSubsystemDutyBtn;
	    //}}AFX_DATA

        /**
          * convertColourStrToColorref
          *
          * Converts a comma delimited set of RGB values into a COLORREF.
          *
          * @param colourStr The colour string.
          * @param defaultColour The colour to use if a problem was found during the conversion.
          *
          * @return COLORREF to the converted colour.
          */
        COLORREF convertColourStrToColorref( const std::string& colourStr, const COLORREF& defaultColour ) const;

        /**
          * determineCellBkColour
          *
          * Determines the colour to shade the cell represented by the matrix element.
          *
          * @param inRegion Specifies whether the subsystem is in the region.
          * @param state Specifies the current state of the subsystem.
          *
          * @return COLORREF The colour to shade the cell.
          */
        COLORREF determineCellBkColour( const bool inRegion, const TA_Base_Bus::ESubsystemState state ) const;

        //CGridCtrl m_subsystemDutyGrid; //TD15533
		CGridCtrlS m_subsystemDutyGrid; //TD15533

        //TA_Base_Bus::DutyAgentAccess m_dutyAgent;
        //TA_Base_Bus::DutyRights m_dutyRights;
        //TA_Base_Bus::DataCache& m_dataCache;
        //TA_Base_Bus::SessionCache& m_sessionCache;
        //TA_Base_Bus::SubsystemDutyMatrix& m_subsystemDutyMatrix;
        //TA_Base_Bus::SessionInfoEx m_currentSessionInfo;

        COLORREF m_normalDutyColour;
        COLORREF m_delegatedDutyColour;
        COLORREF m_degradedDutyColour;
        COLORREF m_unallocatedSubsystemColour;

		//TD15533++
		//std::vector<TA_Base_App::PSSA> m_actionGroupsDB;

		//TA_Base_Bus::ActionGroupKey getActionGroupDB(
		//	const TA_Base_Bus::ProfileKey profileKey,
		//	const TA_Base_Bus::SubsystemKey subsystemKey,
		//	const TA_Base_Bus::ESubsystemState subsystemState);

		TA_Base_App::CellData generateCellData(
			const TA_Base_Bus::SubsystemKey subsystemKey, 
			const TA_Base_Bus::RegionKey regionKey,
			const TA_Base_Bus::ESubsystemState subsystemState);

		TA_Base_App::ProfilesWithDuties getProfilesWithDuties(
			const TA_Base_Bus::SubsystemKey subsystemKey,
			const TA_Base_Bus::RegionKey regionKey);

		std::string getActionGroupNameWithErrorChecking(
			const TA_Base_Bus::ActionGroupKey actionGroupKey);

		bool isSubsystemAccessible(
			const TA_Base_Bus::ProfileKeyList profileKeys,
			const TA_Base_Bus::SubsystemKey subsystemKey);

		TA_Base_Bus::ProfileKeyList getProfileKeyList(
			const TA_Base_Bus::SubsystemKey subsystemKey,
			const TA_Base_Bus::RegionKey regionKey);

		//TA_Base_Bus::RegionKeyList getLocations();

		//bool isRegionAccessible(
		//	const TA_Base_Bus::RegionKey regionKey,
		//	const TA_Base_Bus::RegionKeyList regionKeys);
		//++TD15533

		//+++++++++++++++++++
		SubsystemDutyPropertyPageModel* m_realPModel;
    };

} // namespace TA_Base_App

#endif // !defined(AFX_SUBSYSTEMDUTYPROPERTYPAGE_H__2DD28A53_0AA4_4153_9C2F_8004F3884A5B__INCLUDED_)
