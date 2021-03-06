/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/app/scheduling/scheduling_manager/src/SchedulingManagerView.cpp $
  * @author:  San Teo
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2015/10/09 15:42:35 $
  * Last modified by:  $Author: CM $
  * 
  * Displays the list of jobs that are known to the Scheduling Agent.  It will pass user requests related to 
  * jobs to the document object.
  */

#include <algorithm>

#include "app/scheduling/scheduling_manager/src/stdafx.h"
#include "app/scheduling/scheduling_manager/src/SchedulingManager.h"
#include "app/scheduling/scheduling_manager/src/SchedulingManagerView.h"
#include "app/scheduling/scheduling_manager/src/SchedulingManagerConstants.h"
#include "app/scheduling/scheduling_manager/src/JobDialog.h"
#include "app/scheduling/scheduling_manager/plugin/model/src/Schedule.h"
#include "app/scheduling/scheduling_manager/plugin/model/src/Job.h"
#include "app/scheduling/scheduling_manager/src/IJobDetailsPlugin.h" //TD16070

#include "bus/mfc_extensions/src/print_list_ctrl/ListCtrlPrint.h"
#include "bus/mfc_extensions/src/Resource.h"
#include "bus/generic_gui_view/src/TransActiveMessage.h"
#include "bus/generic_gui_view/src/HelpLauncher.h"
#include "bus/unicode_common_lib/src/TAUnicodeString.h"

#include "core/exceptions/src/SchedulingManagerException.h"
#include "core/utilities/src/TAAssert.h"
#include "core/utilities/src/DebugUtil.h"
#include "core/data_access_interface/src/ProfileAccessFactory.h"
#include "core/data_access_interface/src/LocationAccessFactory.h"
#include "core/data_access_interface/src/IProfile.h"
#include "core/data_access_interface/src/ILocation.h"
#include "core/data_access_interface/entity_access/src/EntityAccessFactory.h"
#include "core/data_access_interface/src/ResourceAccessFactory.h"
#include "core/data_access_interface/entity_access/src/IEntityData.h"
#include "core/data_access_interface/src/IResource.h"
#include "core/data_access_interface/src/OperatorAccessFactory.h"
#include "core/utilities/src/RunParams.h"
#include "core/utilities/src/DateFormat.h" // TD12474 


using namespace TA_Base_App::SchedulingManager;
using TA_Base_Bus::TransActiveMessage;
using TA_Base_Bus::AutoSortListCtrl;
using TA_Base_Core::SchedulingManagerException;
using TA_Base_Core::DebugUtil;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace TA_Base_App
{
    const int NUM_TYPES_WITH_NO_ASSOCIATED_PLUGIN = 1;

    const std::string TYPES_WITH_NO_ASSOCIATED_PLUGIN[NUM_TYPES_WITH_NO_ASSOCIATED_PLUGIN] =
    {
        "AlarmGeneratorJob"
    };
	//cl-16406-lkm
    // Settings for each column
    const CSchedulingManagerView::ColumnInfo CSchedulingManagerView::COLUMN_INFO[CSchedulingManagerView::NumColumnType] = 
    {   {Status,		70,		IDS_COLUMN_STATUS,			AutoSortListCtrl::BY_STRING},//50
        {Type,			60,		IDS_COLUMN_TYPE,			AutoSortListCtrl::BY_STRING},//75
        {Description,	660,	IDS_COLUMN_DESCRIPTION,		AutoSortListCtrl::BY_STRING},//250
        {ScheduleStart, 120,	IDS_COLUMN_SCHEDULE_START,	AutoSortListCtrl::BY_CALLBACK},//125
        {Recurrence,	90,		IDS_COLUMN_RECURRENCE,		AutoSortListCtrl::BY_CALLBACK},//75
        {ScheduleEnd,	120,	IDS_COLUMN_SCHEDULE_END,	AutoSortListCtrl::BY_CALLBACK},//125
        {Profile,		85,	IDS_COLUMN_PROFILE,			AutoSortListCtrl::BY_STRING},//75
        {Location,		85,	IDS_COLUMN_LOCATION,		AutoSortListCtrl::BY_STRING}//75  //zhongjie++
    };
	//cl-16406-lkm
    /////////////////////////////////////////////////////////////////////////////
    // CSchedulingManagerView

IMPLEMENT_DYNCREATE(CSchedulingManagerView, CListView)

BEGIN_MESSAGE_MAP(CSchedulingManagerView, CListView)
    //{{AFX_MSG_MAP(CSchedulingManagerView)
    ON_COMMAND(ID_VIEW_JOBDETAILS, onViewJobdetails)
    ON_COMMAND(ID_JOB_ADD, onJobAdd)
    ON_COMMAND(ID_JOB_DELETE, onJobDelete)
    ON_COMMAND(ID_JOB_DISABLE, onJobDisable)
    ON_COMMAND(ID_JOB_EDIT, onJobEdit)
    ON_COMMAND(ID_JOB_ENABLE, onJobEnable)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, onItemchanged)
    ON_MESSAGE(WM_JOB_CREATE, onCreateJob)
    ON_MESSAGE(WM_JOBLIST_UPDATE, onUpdateJobList)
    ON_MESSAGE(WM_JOB_DELETED, onJobDeleted)
    ON_MESSAGE(WM_JOB_UPDATED, onJobUpdated)
    ON_MESSAGE(WM_SHOW_EXCEED_MAX_JOB_DLG, onShowExceedMaxJobDlg)
	ON_COMMAND(ID_FILE_PRINT, onFilePrint)

	ON_COMMAND(ID_VIEW_ALLJOBS, onViewAlljobs)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALLJOBS, onUpdateViewAlljobs)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_HELP_SCHEDULINGMANAGER, OnHelpSchedulingmanager)
	ON_MESSAGE(WM_TASETLANG, &CSchedulingManagerView::OnSetLanguage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

    /////////////////////////////////////////////////////////////////////////////
    // CSchedulingManagerView construction/destruction

    CSchedulingManagerView::CSchedulingManagerView() :
		m_listCtrl(GetListCtrl()),
		m_sortInfo(NumColumnType),
		m_jobManager(NULL),
		m_isProfileFilterOn(true)
    {
	    FUNCTION_ENTRY( "Constructor" );
		m_printoutColWidths = NULL;//cl-16406-lkm
        for(int i = 0; i < NUM_TYPES_WITH_NO_ASSOCIATED_PLUGIN; ++i)
        {
            m_typesWithoutPlugin.push_back(TYPES_WITH_NO_ASSOCIATED_PLUGIN[i]);
        }

        // load the strings from string table here so that we don't have to repeatedly load them
		INHIBITED_STRING = TALoadString(IDS_INHIBITED);
        TA_VERIFY(!INHIBITED_STRING.IsEmpty(), "String does not exist in string table");
        UNINHIBITED_STRING = TALoadString(IDS_UNINHIBITED);
        TA_VERIFY(!UNINHIBITED_STRING.IsEmpty(), "String does not exist in string table");
        RECUR_NONE_STRING = TALoadString(IDS_RECUR_NONE);
        TA_VERIFY(!RECUR_NONE_STRING.IsEmpty(), "String does not exist in string table");
        RECUR_DAILY_STRING = TALoadString(IDS_RECUR_DAILY);
        TA_VERIFY(!RECUR_DAILY_STRING.IsEmpty(), "String does not exist in string table");
        RECUR_WEEKLY_STRING = TALoadString(IDS_RECUR_WEEKLY);
        TA_VERIFY(!RECUR_WEEKLY_STRING.IsEmpty(), "String does not exist in string table");
        RECUR_MONTHLY_STRING = TALoadString(IDS_RECUR_MONTHLY);
        TA_VERIFY(!RECUR_MONTHLY_STRING.IsEmpty(), "String does not exist in string table");
		RECUR_YEARLY_STRING = TALoadString(IDS_RECUR_YEARLY);
        TA_VERIFY(!RECUR_YEARLY_STRING.IsEmpty(), "String does not exist in string table");

		FUNCTION_EXIT;
    }


    CSchedulingManagerView::~CSchedulingManagerView()
    {
	    FUNCTION_ENTRY( "Destructor" );
        m_toolTip.Detach();

		if (m_printoutColWidths != NULL)
		{
			delete m_printoutColWidths;
			m_printoutColWidths = NULL;
		}

	    FUNCTION_EXIT;
    }

    BOOL CSchedulingManagerView::PreCreateWindow(CREATESTRUCT& cs)
    {
	    FUNCTION_ENTRY( "PreCreateWindow" );
        if (!CListView::PreCreateWindow (cs))
            return FALSE;

        cs.style &= ~LVS_TYPEMASK;
        cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS;

	    FUNCTION_EXIT;
        return TRUE;
    }

    //void CSchedulingManagerView::initialise(const std::vector<std::string>& jobTypes)
	void CSchedulingManagerView::initialise(TA_Base_Bus::ITransActiveWinApp * winApp, JobManager* jobManager)
    {
	    FUNCTION_ENTRY( "initialise" );
		std::vector<std::string> jobTypes;
		try
		{
			m_jobManager = jobManager;

			jobTypes = m_jobManager->getJobTypes();
		}
		catch (SchedulingManagerException& ex)
		{
			bool ok = false;
			TransActiveMessage userMsg;
			unsigned long errorId;
			TAUnicodeString action, agent;
			action = TALoadString(IDS_INITIALISE_APP);
			TA_VERIFY(!action.IsEmpty(), "String does not exist in string table");
			if (ex.getFailType() != SchedulingManagerException::ACCESS_DENIED)
			{
				userMsg << action;
			}

			switch(ex.getFailType())
			{
			case SchedulingManagerException::SCHEDULING_AGENT_FAILURE: // Couldn't contact the scheduling agent
				agent = TALoadString(IDS_SCHEDULING_AGENT);
				TA_VERIFY(!agent.IsEmpty(), "String does not exist in string table");
				userMsg << agent;
				errorId = IDS_UE_030080;
				break;
			case SchedulingManagerException::RIGHTS_AGENT_FAILURE:   // Couldn't contact the rights agent
				agent = TALoadString(IDS_RIGHTS_AGENT);
				TA_VERIFY(!agent.IsEmpty(), "String does not exist in string table");
				userMsg << agent;
				errorId = IDS_UE_030080;
				break;
			case SchedulingManagerException::UNKNOWN_EXCEPTION:      // Unknown exception is thrown
				userMsg << action;
				break;
			case SchedulingManagerException::ACCESS_DENIED:          // Session has insufficient rights to perform action
				{
					errorId = IDS_UE_250017;
					//std::string userName;
					//std::string sessionId = TA_Base_Core::RunParams::getInstance().get(RPARAM_SESSIONID);
					//TA_Base_Bus::AuthenticationLibrary authLibrary(true);
					//TA_Base_Bus::SessionInfo sessionInfo = authLibrary.getSessionInfo(sessionId, sessionId);
					//std::auto_ptr<TA_Base_Core::IOperator> iOperator(TA_Base_Core::OperatorAccessFactory::getInstance().getOperator(sessionInfo.UserId, false));
					//userName = iOperator->getName();
					//userMsg << userName;
					//userMsg << action;
					break;
				}
			case SchedulingManagerException::DATABASE_ERROR:         // Unable to use the database 
				errorId = IDS_UE_250016;
				break;
			case SchedulingManagerException::DATA_ERROR:             // Error in database configuration
				errorId = IDS_UE_010011;
				break;
			case SchedulingManagerException::BAD_SCHEDULE:           // Some jobs contained bad schedules, but it's ok to continue
			case SchedulingManagerException::NO_DAY_OF_WEEK:         // The day of week is not specified in weekly tasks
				ok = true;
				break;
			default:
				TA_ASSERT(false, "Unknown exception type");
			}
			if (!ok)
			{
				userMsg.showMsgBox(errorId);

				delete m_jobManager;
				m_jobManager = NULL;

				// close the application
				AfxGetMainWnd()->PostMessage(WM_CLOSE);
				FUNCTION_EXIT;
				return;
			}
		}
		m_pWinApp = winApp;
        m_jobTypes = jobTypes;
	    FUNCTION_EXIT;
    }


    void CSchedulingManagerView::OnInitialUpdate() 
    {
	    FUNCTION_ENTRY( "OnInitialUpdate" );
	
        m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP |LVS_EX_INFOTIP);
		m_printoutColWidths = new int [CSchedulingManagerView::NumColumnType + 1];//cl-16406-lkm
        for (int i = 0; i < CSchedulingManagerView::NumColumnType; i++)
        {
            TAUnicodeString columnName = TALoadString(COLUMN_INFO[i].name);

            TA_VERIFY(!columnName.IsEmpty(), "String does not exist in string table");
            m_listCtrl.InsertColumn (i, columnName.c_str(), LVCFMT_LEFT, COLUMN_INFO[i].width);
            m_sortInfo.defineSortingSemantic(i, COLUMN_INFO[i].sortBy);
			m_printoutColWidths[i+1] = COLUMN_INFO[i].width-20;//cl-16406-lkm
        }

        // sort callback for item data
        m_sortInfo.setCallback(this);

        // get the tool tip.  Copied from alarm list ctrl
        HWND toolTipHandle = reinterpret_cast<HWND>(SendMessage(LVM_GETTOOLTIPS,0,0));
        m_toolTip.Attach(toolTipHandle);
        m_toolTip.SetDelayTime(TTDT_AUTOPOP,86400000);
        m_toolTip.SetMaxTipWidth(100);

		CListView::OnInitialUpdate();
	    FUNCTION_EXIT;
    }


    void CSchedulingManagerView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
    {
	    FUNCTION_ENTRY( "OnUpdate" );
		//TD18095,jianghp
		m_pMainFrmModel->initRightLib();
		//TD18095,jianghp
        onUpdateJobList(NULL, NULL);
	    FUNCTION_EXIT;
    }


    LRESULT CSchedulingManagerView::onUpdateJobList(WPARAM, LPARAM)
    {
	    FUNCTION_ENTRY( "onUpdateJobList" );
		bool rightsAgentContactable = m_pMainFrmModel->isRightsAgentContactable();

        // don't update the view until our doc is initialised.  Otherwise it'll crash when we try to fetch the data.
        if (NULL == m_jobManager)
        {
            LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "The document hasn't been initialised yet, so don't update view");
            return 0;
        }

        static bool firstUpdate = true;

        CWaitCursor wait;   // display wait cursor
        // The last time that the job list has changed
        static time_t lastUpdateTime = NULL;
        static bool lastFilter = m_isProfileFilterOn;
        m_isUpdating = true;    // flag to stop the onItemchanging from updating the toolbar

        //time_t currentUpdateTime = GetDocument()->getLastUpdateTime();
		time_t currentUpdateTime = m_jobManager->getLastUpdateTime();
        bool currentFilter = m_isProfileFilterOn;
        if ((currentUpdateTime == lastUpdateTime) && (currentFilter == lastFilter))
        {
            LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "We've already updated the view using the latest job list, reinstate the enabling conditions on the toolbar");

            // Tell the main frame that the job selection has changed so that it could enable/disable the toolbar buttons 
            JobPtrVector* selected = new JobPtrVector();
            getSelections(*selected);
            if(rightsAgentContactable)
			{
				AfxGetMainWnd()->PostMessage(WM_JOBSELECTION_CHANGE, reinterpret_cast<WPARAM>(selected), false);
			}
			else
			{
				AfxGetMainWnd()->PostMessage(WM_RIGHTS_AGENT_DIED);
			}

            return 0;
        }
        lastUpdateTime = currentUpdateTime;
        lastFilter = currentFilter;
        
        // get the currently selected items if there's any
        JobPtrVector selections;
        getSelections(selections);
        // std::vector<TA_Base_Bus::SchedulingAgentCorbaDef::JobID> selectedIds;
		std::vector<std::string> selectedIds;
		unsigned int i = 0;
        for (; i < selections.size(); i++)
        {
            selectedIds.push_back(std::string(selections[i]->getId()));
        }

        m_listCtrl.DeleteAllItems();

        //JobPtrMap jobs = GetDocument()->getAllJobs();
		JobPtrMap jobs = getAllJobs();
        unsigned int size = jobs.size();

		LOG_GENERIC(
			SourceInfo, DebugUtil::DebugInfo,
			"[TD16068] size: %lu", size);
		LOG_GENERIC(
			SourceInfo, DebugUtil::DebugInfo,
			"[TD16068] MAX_JOB_TO_DISPLAY: %lu", MAX_JOB_TO_DISPLAY);

        if (size == 0)
        {
            // if there's no jobs, then just post the message back to the main frame to update its toolbar
            if(rightsAgentContactable)
			{
	            AfxGetMainWnd()->PostMessage(WM_JOBSELECTION_CHANGE, NULL, true);
			}
			else
			{
				AfxGetMainWnd()->PostMessage(WM_RIGHTS_AGENT_DIED);
			}
            m_isUpdating = false;
            return 0;
        }
        else if (size > MAX_JOB_TO_DISPLAY)
        {
			LOG_GENERIC(
				SourceInfo, DebugUtil::DebugInfo,
				"[TD16068] size > MAX_JOB_TO_DISPLAY");

            PostMessage(WM_SHOW_EXCEED_MAX_JOB_DLG, 0, 0);
            size = MAX_JOB_TO_DISPLAY;
        }
		else
		{
			LOG_GENERIC(
				SourceInfo, DebugUtil::DebugInfo,
				"[TD16068] size != 0 AND size <= MAX_JOB_TO_DISPLAY");
		}

        JobPtrVector* selectedItem = new JobPtrVector;
        i = 0;
        for (JobPtrMap::iterator job = jobs.begin(); job != jobs.end(); job++)
        {
            if (i >= size)
            {
                // jump out of loop if we've already got the maximum number of items
                break;
            }
            // std::vector<TA_Base_Bus::SchedulingAgentCorbaDef::JobID>::iterator id = std::find(selectedIds.begin(), selectedIds.end(), job->first);
			std::vector<std::string>::iterator id = std::find(selectedIds.begin(), selectedIds.end(), job->first);
            if (id != selectedIds.end())
            {
                selectedItem->push_back(job->second);
            }
            m_listCtrl.InsertItem(i, _T(""));   // don't really need for search etc, so just leave it blank
            populateItem(i, *job->second);
            i++;
        }

        // if this is the first time the list has been built, we want to sort the list by Status, Type, Schedule Start
        // so what we do is we sort in reverse: Schedule Start > Type > Status
        if (firstUpdate)
        {
            // Schedule Start
            m_sortInfo.setCurrentSort(ScheduleStart, AutoSortListCtrl::ASCENDING);
            // Make label column the active sorting column
            m_sortInfo.activateSort(ScheduleStart);
            TA_Base_Bus::AutoSortListCtrl::reApplyCurrentSort(m_listCtrl, m_sortInfo);

            // Type
            m_sortInfo.setCurrentSort(Type, AutoSortListCtrl::ASCENDING);
            // Make label column the active sorting column
            m_sortInfo.activateSort(Type);
            TA_Base_Bus::AutoSortListCtrl::reApplyCurrentSort(m_listCtrl, m_sortInfo);

            // Status
            m_sortInfo.setCurrentSort(Status, AutoSortListCtrl::DESCENDING);
            // Make label column the active sorting column
            m_sortInfo.activateSort(Status);
            TA_Base_Bus::AutoSortListCtrl::reApplyCurrentSort(m_listCtrl, m_sortInfo);

            firstUpdate = false;
        }
        else
        {
            LVFINDINFO info;
            int index;

            info.flags = LVFI_PARAM;
            for (i = 0; i < selectedItem->size(); i++)
            {
                info.lParam = reinterpret_cast<LPARAM>((*selectedItem)[i]);

                if ((index = m_listCtrl.FindItem(&info)) != -1)
                {
        	        m_listCtrl.SetItemState(index, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
                }
            }
        }

        if(rightsAgentContactable)
		{
	        AfxGetMainWnd()->PostMessage(WM_JOBSELECTION_CHANGE, reinterpret_cast<WPARAM>(selectedItem), true);
		}
		else
		{
			AfxGetMainWnd()->PostMessage(WM_RIGHTS_AGENT_DIED);
		}

        m_isUpdating = false;   // onItemchanging can update the toolbar now

        updateNumJobsStatus();

	    FUNCTION_EXIT;
        return 0;
    }


    void CSchedulingManagerView::populateItem(int index, Job& job)
    {
		ProfileMap profiles = m_jobManager->getAllSchedulableProfiles();
		LocationMap locations = m_jobManager->getAllLocations();

        m_listCtrl.SetItemText(index, Status, job.isInhibited() ? INHIBITED_STRING.c_str() : UNINHIBITED_STRING.c_str());

		TAUnicodeString uniStrForType = TAUnicodeString::CreateFromMultitByteString(job.getType().c_str());
        m_listCtrl.SetItemText(index, Type, uniStrForType.c_str());

		TAUnicodeString uniStrForDesc = TAUnicodeString::CreateFromMultitByteString(job.getDescription().c_str());
        m_listCtrl.SetItemText(index, Description, uniStrForDesc.c_str());

		LOG_GENERIC(
			SourceInfo, DebugUtil::DebugDebug,
			"[TD16068] [%lu] Inserted job with description: %s", 
			index, job.getDescription().c_str());

        COleDateTime* startDate = job.getStartDate();
        if (startDate != NULL)
        {
			// TD12474 ++
            //m_listCtrl.SetItemText(index, ScheduleStart, startDate->Format(DATE_TIME_FORMAT));

			TA_Base_Core::DateFormat dateFormat; 
			std::string dateFormatStr = dateFormat.getDateFormat(TA_Base_Core::DateFormat::DateTimeFormat4);

			TAUnicodeString tmpUniStrForDate = TAUnicodeString::CreateFromMultitByteString(dateFormatStr.c_str());
			TAUnicodeString uniStrForDate = startDate->Format(tmpUniStrForDate.c_str());
			std::string itemColDesc = uniStrForDate.toMultiByteStdString();
			TAUnicodeString tmpUniStr = TAUnicodeString::CreateFromMultitByteString(itemColDesc.c_str());
			m_listCtrl.SetItemText(index, ScheduleStart, tmpUniStr.c_str());
			// ++ TD12474
        }
		else
		{	
			//TD16357++
			LOG_GENERIC(SourceInfo, DebugUtil::DebugInfo, "[TD16357]Setting plan schedule start to null");
			m_listCtrl.SetItemText(index, ScheduleStart, _T(""));
			//++TD16357
		}


        TAUnicodeString type;
        switch (job.getSchedule().getType())
        {
        case OnceOff:
            type = RECUR_NONE_STRING;
            break;
        case Daily:
            type = RECUR_DAILY_STRING;
            break;
        case Weekly:
            type = RECUR_WEEKLY_STRING;
            break;
        case Monthly:
            type = RECUR_MONTHLY_STRING;
            break;
        case Yearly:
            type = RECUR_YEARLY_STRING;
            break;
        default:
            TA_ASSERT(false, "Unknown recurrence type");
        }
        m_listCtrl.SetItemText(index, Recurrence, type.c_str());
        COleDateTime* endDate = job.getSchedule().getEndDate();

		// TD12474 ++
		//m_listCtrl.SetItemText(index, ScheduleEnd, (endDate==NULL)?"":endDate->Format(DATE_TIME_FORMAT));
        if (endDate==NULL)
        {
			m_listCtrl.SetItemText(index, ScheduleEnd, _T(""));
        }
		else
		{
			TA_Base_Core::DateFormat dateFormat; 
			std::string dateFormatStr = dateFormat.getDateFormat(TA_Base_Core::DateFormat::DateTimeFormat4);

			TAUnicodeString tmpUniStrForDate = TAUnicodeString::CreateFromMultitByteString(dateFormatStr.c_str());
			TAUnicodeString uniStrEndDate = endDate->Format(tmpUniStrForDate.c_str());
			std::string itemColDesc = uniStrEndDate.toMultiByteStdString();
			TAUnicodeString tmpUniStr = TAUnicodeString::CreateFromMultitByteString(itemColDesc.c_str());
			m_listCtrl.SetItemText(index, ScheduleEnd, tmpUniStr.c_str());
			delete endDate;
		}

		// ++ TD12474
       
        ProfileMap::iterator theProfile = profiles.find(job.getProfileId());
        if (theProfile != profiles.end())
        {
			TAUnicodeString uniStrForProfile = TAUnicodeString::CreateFromMultitByteString(theProfile->second->getName().c_str());
            m_listCtrl.SetItemText(index, Profile, uniStrForProfile.c_str());

            if (theProfile->second->requiresLocationToBeSelected())
            {
                LocationMap::iterator theLocation = locations.find(job.getLocationId());
                if (theLocation != locations.end())
                {
					TAUnicodeString uniStrForLocation = TAUnicodeString::CreateFromMultitByteString(theLocation->second->getDisplayName().c_str());
                    m_listCtrl.SetItemText(index, Location, uniStrForLocation.c_str());
                }
            }
        }

        // Set item data to allow searches/sorting
        m_listCtrl.SetItemData(index, reinterpret_cast<DWORD>(&(job)));
    }


    LRESULT CSchedulingManagerView::onJobDeleted(WPARAM theJob, LPARAM)
    {
	    FUNCTION_ENTRY( "onJobDeleted" );

        CWaitCursor wait;   // display wait cursor

        Job* job = reinterpret_cast<Job*>(theJob);
        if (theJob == NULL)
        {
            LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugDebug, "Deleting NULL job, ignoring");
    	    FUNCTION_EXIT;
            return 0;
        }
        LVFINDINFO info = {LVFI_PARAM, NULL, theJob, NULL, NULL};
        int index = m_listCtrl.FindItem(&info);
        if (index >= 0)
        {
            m_listCtrl.DeleteItem(index);

			LOG_GENERIC(
				SourceInfo, DebugUtil::DebugInfo,
				"[TD16068] getJobCount(): %lu", getJobCount());
			LOG_GENERIC(
				SourceInfo, DebugUtil::DebugInfo,
				"[TD16068] MAX_JOB_TO_DISPLAY: %lu", MAX_JOB_TO_DISPLAY);

            if (getJobCount() >= MAX_JOB_TO_DISPLAY)
            {
				LOG_GENERIC(
					SourceInfo, DebugUtil::DebugInfo,
					"[TD16068] getJobCount() >= MAX_JOB_TO_DISPLAY");

                // if we were displaying the maximum number of jobs initially and we've deleted one, we now
                // have space to insert the next one, so just let it update the entire list
                PostMessage(WM_JOBLIST_UPDATE, 0, 0);
            }
            else
            {
				LOG_GENERIC(
					SourceInfo, DebugUtil::DebugInfo,
					"[TD16068] getJobCount() < MAX_JOB_TO_DISPLAY");

                // Otherwise, we don't have to rebuild the list, just update the status to show how how many jobs are left
                updateNumJobsStatus();
            }

        }
        delete job;
        job = NULL;

        // Tell the main frame that the job selection has changed so that it could enable/disable the toolbar buttons 
        JobPtrVector* selected = new JobPtrVector();
        getSelections(*selected);
        if(m_pMainFrmModel->isRightsAgentContactable())
		{
	        AfxGetMainWnd()->PostMessage(WM_JOBSELECTION_CHANGE, reinterpret_cast<WPARAM>(selected), false);
		}
		else
		{
			AfxGetMainWnd()->PostMessage(WM_RIGHTS_AGENT_DIED);
		}

	    FUNCTION_EXIT;
        return 0;
    }


    LRESULT CSchedulingManagerView::onJobUpdated(WPARAM theJob, LPARAM)
    {
	    FUNCTION_ENTRY( "onJobUpdated" );

        CWaitCursor wait;   // display wait cursor

        Job* job = reinterpret_cast<Job*>(theJob);
        if (theJob == NULL)
        {
            LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugDebug, "Updating/Adding NULL job, ignoring");
    	    FUNCTION_EXIT;
            return 0;
        }
        LVFINDINFO info = {LVFI_PARAM, NULL, theJob, NULL, NULL};
        int index = m_listCtrl.FindItem(&info);
        int totalItems = m_listCtrl.GetItemCount();

		bool profileFound = false;
		//std::vector<unsigned long> profilesToMatch = GetDocument()->getSessionProfiles();
		std::vector<unsigned long> profilesToMatch = m_jobManager->getSessionProfiles();
		for (unsigned int i=0; i<profilesToMatch.size(); i++)
        {
            LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugInfo, "** %u==%u?", job->getProfileId(), profilesToMatch[i]);
            if (job->getProfileId() == profilesToMatch[i])
            {
                profileFound = true;
                break;
            }
        }
		
		// we'll update the item if:
		//    - the profile filter is OFF; all items are displayed and need to be updated.
		//      OR
		//    - the profile filter is ON, AND the profile matches the current filter.
		if (!m_isProfileFilterOn || profileFound)
		{
			// was the job not found in the list?
			if (index < 0)
			{
				LOG_GENERIC(
					SourceInfo, DebugUtil::DebugInfo,
					"[TD16068] totalItems: %lu", totalItems);
				LOG_GENERIC(
					SourceInfo, DebugUtil::DebugInfo,
					"[TD16068] MAX_JOB_TO_DISPLAY: %lu", MAX_JOB_TO_DISPLAY);

				if (totalItems == MAX_JOB_TO_DISPLAY)
				{
					LOG_GENERIC(
						SourceInfo, DebugUtil::DebugInfo,
						"[TD16068] totalItems == MAX_JOB_TO_DISPLAY");

					LOG_GENERIC(
						SourceInfo, DebugUtil::DebugInfo,
						"[TD16068] getJobCount(): %lu", getJobCount());

					// we've already showing max number of jobs and this job hasn't been added yet
					// so just tell the user that we're not going to display this job
					if (getJobCount() == MAX_JOB_TO_DISPLAY + 1)
					{
						LOG_GENERIC(
							SourceInfo, DebugUtil::DebugInfo,
							"[TD16068] getJobCount() == MAX_JOB_TO_DISPLAY + 1");

						// only tell the operator once when it hits the limit, so that the operator doesn't
						// get a message for each job over the max limit
						PostMessage(WM_SHOW_EXCEED_MAX_JOB_DLG, 0, 0);
					}
					else
					{
						LOG_GENERIC(
							SourceInfo, DebugUtil::DebugInfo,
							"[TD16068] getJobCount() != MAX_JOB_TO_DISPLAY + 1");
					}

					updateNumJobsStatus();
					LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugDebug, "The list is already showing max number of jobs, not going to display job = %s", job->getId().c_str());
					FUNCTION_EXIT;
					return 0;
				}

				// insert the item cos it's not there yet
				index = totalItems;
				m_listCtrl.InsertItem(index, _T(""));   // don't really need for search etc, so just leave it blank
				updateNumJobsStatus();
				LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugDebug, "Adding job = %s into the view", job->getId().c_str());
			}

			// update/start populating the jobs
			populateItem(index, *job);
		}
		// the profile filter is ON, and the profile does NOT match the current filter
		else
		{
			// was the job found in the list?
			// if it was, remove it. it no longer matches the filter
			if (index >= 0)
			{
				m_listCtrl.DeleteItem(index);
			}
			// else do nothing - the job is not in the list, and will remain so.
		}

        // Tell the main frame that the job selection has changed so that it could enable/disable the toolbar buttons 
        JobPtrVector* selected = new JobPtrVector();
        getSelections(*selected);
        if(m_pMainFrmModel->isRightsAgentContactable())
		{
	        AfxGetMainWnd()->PostMessage(WM_JOBSELECTION_CHANGE, reinterpret_cast<WPARAM>(selected), false);
		}
		else
		{
			AfxGetMainWnd()->PostMessage(WM_RIGHTS_AGENT_DIED);
		}

        FUNCTION_EXIT;
        return 0;
    }

    
    void CSchedulingManagerView::updateNumJobsStatus()
    {
        // set the status bar text
        int totalNum = getJobCount();
        TAUnicodeString numJobStr;
        numJobStr.str().Format(_T("%d"), totalNum);
        CString* status = new CString();
        AfxFormatString1(*status, IDS_NUM_JOBS_STATUS, numJobStr.c_str());
        AfxGetMainWnd()->PostMessage(WM_STATUSTEXT_CHANGE, reinterpret_cast<WPARAM>(status));
    }


    void CSchedulingManagerView::updateNumJobsProcessed(int resourceId, int numProcessed, int totalNum)
    {
        // set the status bar text
        TAUnicodeString stringFormat = TALoadString(resourceId);
        TA_VERIFY(!stringFormat.IsEmpty(), "String does not exist in string table");
        CString* status = new CString();
        status->Format(stringFormat.c_str(), numProcessed, totalNum);
        AfxGetMainWnd()->PostMessage(WM_STATUSTEXT_CHANGE, reinterpret_cast<WPARAM>(status));
    }


    void CSchedulingManagerView::getSelections(JobPtrVector& selection) 
    {
	    FUNCTION_ENTRY( "getSelection" );
	    POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
        if (pos == NULL)
        {
            LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "Nothing is selected");
            FUNCTION_EXIT;
            return;
        }

        while (pos != NULL)
        {
    	    Job* job = reinterpret_cast<Job*>(m_listCtrl.GetItemData(m_listCtrl.GetNextSelectedItem(pos)));
            if (job != NULL)
            {
                selection.push_back(job);
            }
        }
        FUNCTION_EXIT;
    }


    /////////////////////////////////////////////////////////////////////////////
    // CSchedulingManagerView drawing

    void CSchedulingManagerView::OnDraw(CDC* pDC)
    {
        //CSchedulingManagerDoc* pDoc = GetDocument();
        //ASSERT_VALID(pDoc);
        // TODO: add draw code for native data here
    }

    /////////////////////////////////////////////////////////////////////////////
    // CSchedulingManagerView diagnostics

    #ifdef _DEBUG
    void CSchedulingManagerView::AssertValid() const
    {
        CListView::AssertValid();
    }


    void CSchedulingManagerView::Dump(CDumpContext& dc) const
    {
        CListView::Dump(dc);
    }
    #endif //_DEBUG


    /////////////////////////////////////////////////////////////////////////////
    // CSchedulingManagerView message handlers

    void CSchedulingManagerView::onViewJobdetails() 
    {
	    FUNCTION_ENTRY( "onViewJobdetails" );

        std::vector<Job*> selections;
        getSelections(selections);
        TA_ASSERT(selections.size() == 1, "Should only be allowed to view when only 1 item is selected");

        // Determine if there is a plugin associated
        std::vector<std::string>::iterator it = std::find(m_typesWithoutPlugin.begin(), m_typesWithoutPlugin.end(), selections[0]->getType());
        bool enableSettings = (it == m_typesWithoutPlugin.end());

		JobDialog jobDialog(IDS_VIEW_JOB_DIALOG_TITLE, m_jobTypes, m_jobManager, true, enableSettings, m_pWinApp);
        jobDialog.setData(*selections[0]);
        jobDialog.DoModal();
        FUNCTION_EXIT;
    }


    void CSchedulingManagerView::onJobAdd() 
    {
	    FUNCTION_ENTRY( "onJobAdd" );
        
		// TD #13519
		// check if the rights agent is contactable.
		// if it's not, don't show the add job dialog
		if(m_pMainFrmModel->isRightsAgentContactable())
		{
			JobDialog jobDialog(IDS_ADD_JOB_DIALOG_TITLE, m_jobTypes, m_jobManager, false, true,m_pWinApp);
			//TD16070++
			if (canLoadDLL())
			{
				jobDialog.DoModal();
			}
			//TD16070++
		}
		else
		{
			TA_Base_Bus::TransActiveMessage userMsg;

            TAUnicodeString action = TALoadString(IDS_ADD_JOB);
            TA_VERIFY(!action.IsEmpty(), "String does not exist in string table");
			userMsg << action;

			TAUnicodeString agent = TALoadString(IDS_RIGHTS_AGENT);
            TA_VERIFY(!agent.IsEmpty(), "String does not exist in string table");
            userMsg << agent;
            userMsg.showMsgBox(IDS_UE_030080);
		}

        FUNCTION_EXIT;
    }


    void CSchedulingManagerView::onJobDelete() 
    {
	    FUNCTION_ENTRY( "onJobDelete" );

        std::vector<Job*> selections;
        getSelections(selections);
        TA_ASSERT(!selections.empty(), "Should only be allowed to delete when something is selected");

        TAUnicodeString action = TALoadString(IDS_DELETE);
        TA_VERIFY(!action.IsEmpty(), "String does not exist in string table");
        TA_Base_Bus::TransActiveMessage userMsg;
        userMsg << action;
        UINT selectedButton = userMsg.showMsgBox(IDS_UW_010003);
        if (IDNO == selectedButton)
        {
            LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "Operator chosen not to delete selections");
            FUNCTION_EXIT;
            return;
        }

        unsigned int nSelIndex = 0;
        try
        {
			// TD #13519
			// Most cases, if the rights agent is not contactable, the delete button would have
			// been disabled by now. However if the rights agent died between the user making a
			// new selection and pressing the delete button, we'll get here.
			// Make sure an error dialog is displayed.
			if(!m_pMainFrmModel->isRightsAgentContactable())
			{
				TA_THROW(SchedulingManagerException(SchedulingManagerException::RIGHTS_AGENT_FAILURE));
			}

			bool isLocked=false;

            unsigned int total = selections.size();
            for (nSelIndex = 0; nSelIndex < total; nSelIndex++)
            {
                try
                {
					//TD16352++
					isLocked = isJobEditLockedForSelection(selections[nSelIndex]->getId());

					if(isLocked==true)
					{
						LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "[TD16352]Displaying transactive message with action job id%s", selections[nSelIndex]->getId().c_str());
						TA_Base_Bus::TransActiveMessage userMsg;
						userMsg << action;
						userMsg << selections[nSelIndex]->getId();
						userMsg.showMsgBox(IDS_UE_803006);
					}
					else
					{
						//GetDocument()->deleteJob(selections[nSelIndex]->getId());
						m_jobManager->deleteJob(selections[nSelIndex]->getId());
						updateNumJobsProcessed(IDS_DELETE_JOBS_STATUS, nSelIndex, total);
					}
					//++TD16352
                }
                catch (SchedulingManagerException& ex)
                {
                    switch(ex.getFailType())
                    {
                    case SchedulingManagerException::DATABASE_ERROR:         // Unable to use the database or error in database
                    case SchedulingManagerException::JOB_NOT_EXIST:          // Job does not exist
                    case SchedulingManagerException::SESSION_PROFILES_NOT_MATCH_JOB_PROFILE: // The session profiles do not include one that is associated with the job
                        LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "Unable to delete job %s : %s", selections[nSelIndex]->getId().c_str(), selections[nSelIndex]->getDescription().c_str());//TD14337 yezh++
                        break;
                    default:
                        throw;
                    }
                }
            }
        }
        catch (const SchedulingManagerException& ex)
        {
            TAUnicodeString agent;

            switch(ex.getFailType())
            {
            case SchedulingManagerException::SCHEDULING_AGENT_FAILURE: // Couldn't contact the scheduling agent
				agent = TALoadString(IDS_SCHEDULING_AGENT);
                TA_VERIFY(!agent.IsEmpty(), "String does not exist in string table");
                userMsg << agent;
                userMsg.showMsgBox(IDS_UE_030080);
                break;
            case SchedulingManagerException::RIGHTS_AGENT_FAILURE:   // Couldn't contact the rights agent
				agent = TALoadString(IDS_RIGHTS_AGENT);
                TA_VERIFY(!agent.IsEmpty(), "String does not exist in string table");
                userMsg << agent;
                userMsg.showMsgBox(IDS_UE_030080);
                break;
            case SchedulingManagerException::ACCESS_DENIED:          // Session has insufficient rights to perform action
			{
				//std::string userName;
				TA_Base_Bus::TransActiveMessage userMsg;
				//std::string sessionId = TA_Base_Core::RunParams::getInstance().get(RPARAM_SESSIONID);
				//TA_Base_Bus::AuthenticationLibrary authLibrary(true);
				//TA_Base_Bus::SessionInfo sessionInfo = authLibrary.getSessionInfo(sessionId, sessionId);
				//std::auto_ptr<TA_Base_Core::IOperator> iOperator(TA_Base_Core::OperatorAccessFactory::getInstance().getOperator(sessionInfo.UserId, false));
				//userName = iOperator->getName();
				//userMsg << userName;
				//userMsg << action;
				userMsg.showMsgBox(IDS_UE_250017);
				break;
            }
            case SchedulingManagerException::EDIT_LOCK:          // Session has insufficient rights to perform action
			{
                LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "Can't delete when job is executing");
                std::stringstream stmError;
                stmError << "Unable to delete job " << selections[nSelIndex]->getId()
                    << ", because it is running";
				TAUnicodeString tmpUniStr = TAUnicodeString::CreateFromMultitByteString(stmError.str().c_str());
                ::AfxMessageBox(tmpUniStr.c_str());
                break;
            }
            case SchedulingManagerException::UNKNOWN_EXCEPTION:      // Unknown exception is thrown
            default:
                userMsg.showMsgBox(IDS_UE_250015);
                break;
            }
        }
        FUNCTION_EXIT;
    }

	//TD16352++
	bool CSchedulingManagerView::isJobEditLockedForSelection(const std::string& jobId)
	{
		FUNCTION_ENTRY( "isJobEditLockedForSelection" );

		
		//check for edit locks
		bool isLocked = false;
		try
        {
            //isLocked = GetDocument()->isJobLockedForEdit(jobId);
			isLocked = m_jobManager->isJobLockedForEdit(jobId);
		}
		catch (const SchedulingManagerException& )
        {
			//unexpected to throw any exceptions
			LOG_GENERIC(SourceInfo, DebugUtil::DebugError, "[TD16352]Caught SchedulingManagerException while checking is job edit lock");
			throw;
		}
		catch(...)
		{
			//unexpected to throw any exceptions
			LOG_GENERIC(SourceInfo, DebugUtil::DebugError, "[TD16352]Caught unknown exception while checking is job edit lock");
			throw;
		}

		if(isLocked==true)
		{
			LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "[TD16352]returning edit lock true");
		}
		else
		{
			LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "[TD16352]returning edit lock false");
		}
		

		FUNCTION_EXIT;
		return isLocked;
	}

	void CSchedulingManagerView::updateEditLock(const std::string& jobId, bool lock)
	{
		try
        {
			m_jobManager->updateEditLock(jobId,lock);
		}
		catch (const SchedulingManagerException& ex)
        {
			TA_Base_Bus::TransActiveMessage userMsg;
			TAUnicodeString action = TALoadString(IDS_UPDATE_EDIT_LOCK);

			TA_VERIFY(!action.IsEmpty(), "String does not exist in string table");
			
			switch(ex.getFailType())
            {
				case SchedulingManagerException::JOB_NOT_EXIST:          // Job does not exist
						userMsg << action;
						userMsg.showMsgBox(IDS_UE_250022);
						
						throw;
				default:
                        throw;
			}
		}
		catch(...)
		{
			//unexpected to throw any exceptions
			LOG_GENERIC(SourceInfo, DebugUtil::DebugError, "[TD16352]Caught unknown exception while updating job edit lock");
			throw;
		}
	}
	//++TD16352


    void CSchedulingManagerView::onJobEdit() 
    {
	    FUNCTION_ENTRY( "onJobEdit" );
	    POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
        TA_ASSERT(pos != NULL, "No item selected.  This should be prevented in GUI");

		Job* job = reinterpret_cast<Job*>(m_listCtrl.GetItemData(m_listCtrl.GetNextSelectedItem(pos)));
		if(! job)    //Add by Veld , TD CL-16421
		{
			FUNCTION_EXIT;
			return;
		}
		

		//TD16352++
		TAUnicodeString action = TALoadString(IDS_EDIT_JOB);
		TA_VERIFY(!action.IsEmpty(), "String does not exist in string table");

		bool isLocked=false;
		try        //Add try by Veld , TD CL-16421
		{			
			isLocked = isJobEditLockedForSelection(job->getId());

            if( isLocked )
			{
				TA_Base_Bus::TransActiveMessage userMsg;
				userMsg << action;
				userMsg << job->getDescription();  //userMsg << job->getId();  //by Veld , TD CL-16421
				userMsg.showMsgBox(IDS_UE_803006);

				FUNCTION_EXIT;
				return;
			}
		}
        catch (const SchedulingManagerException& ex)   //by Veld CL-16421
        {
            TransActiveMessage userMsg;
            unsigned long errorId;
            TAUnicodeString agent, itemName;
			TAUnicodeString action = TALoadString(IDS_EDIT_SCHEDULE);	
			TA_VERIFY(!action.IsEmpty(), "String does not exist in string table");
			userMsg << action;
            switch(ex.getFailType())
            {
            case SchedulingManagerException::SCHEDULING_AGENT_FAILURE: // Couldn't contact the scheduling agent	
				agent = TALoadString(IDS_SCHEDULING_AGENT);
                TA_VERIFY(!agent.IsEmpty(), "String does not exist in string table");			
                userMsg << agent;
                errorId = IDS_UE_030080;
                break;
            case SchedulingManagerException::RIGHTS_AGENT_FAILURE:   // Couldn't contact the rights agent
				agent = TALoadString(IDS_RIGHTS_AGENT);
                TA_VERIFY(!agent.IsEmpty(), "String does not exist in string table");	
                userMsg << agent;
                errorId = IDS_UE_030080;
                break;
            case SchedulingManagerException::UNKNOWN_EXCEPTION:      // Unknown exception is thrown
            default:
                errorId = IDS_UE_250015;
                break;
            }
            userMsg.showMsgBox(errorId);			
			FUNCTION_EXIT;
			return;
        }
        catch (...)
        {
            TransActiveMessage userMsg;
            userMsg.showMsgBox( IDS_UE_250015 );
            FUNCTION_EXIT;
            return;
        }		
		//++TD16352


		// TD #13519
		// check if the rights agent is contactable.
		// if it's not, don't show the edit job dialog
		try                                  //Add try by Veld  CL-16421
		{
			if(m_pMainFrmModel->isRightsAgentContactable())
			{
				// Determine if there is a plugin associated
				std::vector<std::string>::iterator it = std::find(m_typesWithoutPlugin.begin(), m_typesWithoutPlugin.end(), job->getType());
				bool enableSettings = (it == m_typesWithoutPlugin.end());
				
				//TD16352++
				//lock for edit
				updateEditLock(job->getId(),true);
				//++TD16352

				JobDialog jobDialog(IDS_EDIT_JOB_DIALOG_TITLE, m_jobTypes, m_jobManager, false, enableSettings,m_pWinApp);
				jobDialog.setData(*job);
				//TD16070++
				if (canLoadDLL())
				{
					jobDialog.DoModal();
				}
				//++TD16070

				//TD16352++
				//unlock finished editing
				updateEditLock(job->getId(),false);//lock for edit
				//++TD16352
			}
			else
			{
				TA_Base_Bus::TransActiveMessage userMsg;
				userMsg << action;

				TAUnicodeString agent = TALoadString(IDS_RIGHTS_AGENT);
				TA_VERIFY(!agent.IsEmpty(), "String does not exist in string table");
				userMsg << agent;
				userMsg.showMsgBox(IDS_UE_030080);
			}
		}		
        catch (const SchedulingManagerException& ex)   //by Veld CL-16421
        {
            TransActiveMessage userMsg;
            unsigned long errorId;            
			TAUnicodeString agent, itemName;
			TAUnicodeString action = TALoadString(IDS_EDIT_SCHEDULE);	
            TA_VERIFY(!action.IsEmpty(), "String does not exist in string table");
			userMsg << action;
            switch(ex.getFailType())
            {
            case SchedulingManagerException::SCHEDULING_AGENT_FAILURE: // Couldn't contact the scheduling agent
				agent = TALoadString(IDS_SCHEDULING_AGENT);
                TA_VERIFY(!agent.IsEmpty(), "String does not exist in string table");
                userMsg << agent;
                errorId = IDS_UE_030080;
                break;
            case SchedulingManagerException::RIGHTS_AGENT_FAILURE:   // Couldn't contact the rights agent
				agent = TALoadString(IDS_RIGHTS_AGENT);
                TA_VERIFY(!agent.IsEmpty(), "String does not exist in string table");
                userMsg << agent;
                errorId = IDS_UE_030080;
                break;
            case SchedulingManagerException::UNKNOWN_EXCEPTION:      // Unknown exception is thrown
            default:
                errorId = IDS_UE_250015;
                break;
            }
            userMsg.showMsgBox(errorId);
            FUNCTION_EXIT;
            return;
        }
        catch (...)
        {
            TransActiveMessage userMsg;
            userMsg.showMsgBox( IDS_UE_250015 );
			FUNCTION_EXIT;
			return;
        }

        FUNCTION_EXIT;
    }


    void CSchedulingManagerView::enable(const bool isEnable) 
    {
	    FUNCTION_ENTRY( "enable" );

        std::vector<Job*> selections;
        getSelections(selections);
        TA_ASSERT(!selections.empty(), "Should only be allowed to delete when something is selected");

        try
        {
			// TD #13519
			// Most cases, if the rights agent is not contactable, the enable/disable buttons would have
			// been disabled by now. However if the rights agent died between the user making a
			// new selection and pressing the enable/delete buttons, we'll get here.
			// Make sure an error dialog is displayed.
			if(!m_pMainFrmModel->isRightsAgentContactable())
			{
				TA_THROW(SchedulingManagerException(SchedulingManagerException::RIGHTS_AGENT_FAILURE));
			}

			//TD16352++
			TAUnicodeString action;
			bool isLocked=false;

			if(isEnable == true)
			{
				action = TALoadString(IDS_DISABLE_JOB);
				TA_VERIFY(!action.IsEmpty(), "String does not exist in string table");
			}
			else
			{
				action = TALoadString(IDS_SAVE_NEW_JOB);
				TA_VERIFY(!action.IsEmpty(), "String does not exist in string table");
			}
			//++TD16352

            unsigned int total = selections.size();
            for (unsigned int i = 0; i < total; i++)
            {
                try
                {
					
					//TD16352++
					isLocked = isJobEditLockedForSelection(selections[i]->getId());

					if(isLocked==true)
					{
							TA_Base_Bus::TransActiveMessage userMsg;
							userMsg << action;
							userMsg << selections[i]->getId();
							userMsg.showMsgBox(IDS_UE_803006);
					}
					else
					{
						//lock for edit
						updateEditLock(selections[i]->getId(),true);

						m_jobManager->enableJob(selections[i]->getId(), isEnable);
						updateNumJobsProcessed(isEnable ? IDS_ENABLE_JOBS_STATUS : IDS_DISABLE_JOBS_STATUS, i, total);

						//remove edit lock
						updateEditLock(selections[i]->getId(),false);
					}
					//++TD16352
                }
                catch (const SchedulingManagerException& ex)
                {
					//TD16069++
					bool bShowMessage=true;
					TransActiveMessage userMsg;
					unsigned long errorId;
					TAUnicodeString agent, itemName;

					if (ex.getFailType() != SchedulingManagerException::ACCESS_DENIED)
					{
						userMsg << action;
					}

					LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "Unable to enable job %s : %s", selections[i]->getId().c_str(), selections[i]->getDescription().c_str());//TD14337 yezh++

                    switch(ex.getFailType())
                    {
					case SchedulingManagerException::TOO_MANY_JOBS:          // Too many jobs are scheduled to start on the same time
						 
						 errorId = IDS_UE_250023;
						 
						 break;
                    case SchedulingManagerException::JOB_IN_PAST:            // Schedule is set to run in the past
						errorId = IDS_UE_250018;
						break;
                    case SchedulingManagerException::NO_JOB_PARAMETER:       // No job specified details are specified
						itemName = TALoadString(IDS_JOB_SETTING);
						TA_VERIFY(!itemName.IsEmpty(), "String does not exist in string table");
						userMsg << itemName;
						errorId = IDS_UE_250014;
						break;
                    case SchedulingManagerException::NO_DAY_OF_WEEK:         // Job contain bad dates etc, output the error returned by agent
						errorId = IDS_UE_250019;
						break;
                    case SchedulingManagerException::BAD_SCHEDULE:           // Schedule is invalid, just assert as the job dialog supposed to stop it
						bShowMessage=false;
						break;
                    case SchedulingManagerException::INVALID_JOB_PARAMETER:  // Job parameters are not configured properly
						errorId = IDS_UE_250020;
						break;
                    case SchedulingManagerException::MISSING_JOB_PARAMETER:  // Job parameters are missing
						errorId = IDS_UE_250021;
						break;
                    case SchedulingManagerException::JOB_NOT_EXIST:          // Job does not exist
						errorId = IDS_UE_250022;
						break;
                    case SchedulingManagerException::SESSION_PROFILES_NOT_MATCH_JOB_PROFILE: // The session profiles do not include one that is associated with the job    
						bShowMessage=false;
                        break;
                    default:
                        throw;
                    }
					
					if(bShowMessage)
					{
						userMsg.showMsgBox(errorId);
					}
					//++TD16069
                }
            }
        }
        catch (const SchedulingManagerException& ex)
        {
            TransActiveMessage userMsg;
            unsigned long errorId;
			TAUnicodeString agent, itemName;
            TAUnicodeString action = TALoadString(isEnable ? IDS_ENABLE_JOB : IDS_DISABLE_JOB); 
            TA_VERIFY(!action.IsEmpty(), "String does not exist in string table");
				
			if (ex.getFailType() != SchedulingManagerException::ACCESS_DENIED)
			{
				userMsg << action;
			}

            switch(ex.getFailType())
            {
            case SchedulingManagerException::SCHEDULING_AGENT_FAILURE: // Couldn't contact the scheduling agent
				agent = TALoadString(IDS_SCHEDULING_AGENT);
                TA_VERIFY(!agent.IsEmpty(), "String does not exist in string table");
                userMsg << agent;
                errorId = IDS_UE_030080;
                break;
            case SchedulingManagerException::RIGHTS_AGENT_FAILURE:   // Couldn't contact the rights agent
				agent = TALoadString(IDS_RIGHTS_AGENT);
                TA_VERIFY(!agent.IsEmpty(), "String does not exist in string table");
                userMsg << agent;
                errorId = IDS_UE_030080;
                break;
            case SchedulingManagerException::ACCESS_DENIED:          // Session has insufficient rights to perform action
					{
						errorId = IDS_UE_250017;
						//std::string userName;
						//std::string sessionId = TA_Base_Core::RunParams::getInstance().get(RPARAM_SESSIONID);
						//TA_Base_Bus::AuthenticationLibrary authLibrary(true);
						//TA_Base_Bus::SessionInfo sessionInfo = authLibrary.getSessionInfo(sessionId, sessionId);
						//std::auto_ptr<TA_Base_Core::IOperator> iOperator(TA_Base_Core::OperatorAccessFactory::getInstance().getOperator(sessionInfo.UserId, false));
						//userName = iOperator->getName();
						//userMsg << userName;
						//userMsg << action;
						break;
					}
            case SchedulingManagerException::DATABASE_ERROR:         // Unable to use the database or error in database
                errorId = IDS_UE_250016;
                break;
            case SchedulingManagerException::UNKNOWN_EXCEPTION:      // Unknown exception is thrown
            default:
                errorId = IDS_UE_250015;
                break;
            }
            userMsg.showMsgBox(errorId);
        }
        FUNCTION_EXIT;
    }


    void CSchedulingManagerView::onJobEnable() 
    {
	    FUNCTION_ENTRY( "onJobEnable" );
        enable(true);
        FUNCTION_EXIT;
    }


    void CSchedulingManagerView::onJobDisable() 
    {
	    FUNCTION_ENTRY( "onJobDisable" );
        enable(false);
        FUNCTION_EXIT;
    }


    void CSchedulingManagerView::onItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
    {
	    FUNCTION_ENTRY( "onItemchanged" );
        // don't want to use pNMHDR cos it'll return a valid index to the list even if no row is selected.  We'll use 
        // GetNextSelectedItem to get the selected item instead.
    	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	    // If the item's state has not changed or the view is in the middle of updating, don't need to inform the main frame
        if (((pNMListView->uChanged & LVIF_STATE) != LVIF_STATE) || m_isUpdating)
        {
            LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "No state change.  Ignore");
            FUNCTION_EXIT;
            return;
        }

        LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "Tell main frame about the selection change");
        // Tell the main frame that the job selection has changed so that it could enable/disable the toolbar buttons 
        JobPtrVector* selected = new JobPtrVector();
        getSelections(*selected);
        if(m_pMainFrmModel->isRightsAgentContactable())
		{
	        AfxGetMainWnd()->PostMessage(WM_JOBSELECTION_CHANGE, reinterpret_cast<WPARAM>(selected), false);
		}
		else
		{
			AfxGetMainWnd()->PostMessage(WM_RIGHTS_AGENT_DIED);
		}
        FUNCTION_EXIT;
    }


    LRESULT CSchedulingManagerView::onCreateJob(WPARAM theJob, LPARAM)
    {
	    FUNCTION_ENTRY( "onCreateJob" );
    
		// TD #13519
		// check if the rights agent is contactable.
		// if it's not, don't show the add job dialog
		if(m_pMainFrmModel->isRightsAgentContactable())
		{
			Job* job = reinterpret_cast<Job*>(theJob);

			// Determine if there is a plugin associated
			std::vector<std::string>::iterator it = std::find(m_typesWithoutPlugin.begin(), m_typesWithoutPlugin.end(), job->getType());
			bool enableSettings = (it == m_typesWithoutPlugin.end());

			JobDialog jobDialog(IDS_ADD_JOB_DIALOG_TITLE, m_jobTypes,m_jobManager, false, enableSettings,m_pWinApp);
			jobDialog.setData(*job);
			jobDialog.DoModal();
			delete job;
			job = NULL;
		}
		else
		{
			TA_Base_Bus::TransActiveMessage userMsg;
            TAUnicodeString action = TALoadString(IDS_ADD_JOB);
            TA_VERIFY(!action.IsEmpty(), "String does not exist in string table");
			userMsg << action;

			TAUnicodeString agent = TALoadString(IDS_RIGHTS_AGENT);
            TA_VERIFY(!agent.IsEmpty(), "String does not exist in string table");
            userMsg << agent;
            userMsg.showMsgBox(IDS_UE_030080);
		}

        FUNCTION_EXIT;
        return 0;
    }


    LRESULT CSchedulingManagerView::onShowExceedMaxJobDlg(WPARAM theJob, LPARAM)
    {
	    FUNCTION_ENTRY( "onShowExceedMaxJobDlg" );
        static bool isShowing = false;

        if (isShowing)
        {
            // it's already showing the message, don't show it again
            LOG_GENERIC(SourceInfo, DebugUtil::DebugDebug, "Already showing the message box, no need to display another one");
            FUNCTION_EXIT;
            return 0;
        }

        // tell the operator that we'll only display the first x number of jobs if the total number of
        // jobs available exceeds what we can display
        isShowing = true;
        TA_Base_Bus::TransActiveMessage userMsg;
        userMsg << MAX_JOB_TO_DISPLAY;
        UINT selectedButton = userMsg.showMsgBox(IDS_UE_250008);
        isShowing = false;
        FUNCTION_EXIT;
        return 0;
    }


    //////////////////////////////////////////////////////////////////////////////////
    //
    //
    // Methods to manipulate sort order etc.. 
    //
    //
    //////////////////////////////////////////////////////////////////////////////////

    LRESULT CSchedulingManagerView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
    {     
        AutoSortListCtrl::WindowProc(message, wParam, lParam, m_listCtrl, m_sortInfo);
        return CListView::WindowProc(message, wParam, lParam);
    }


	//jinhua++ TD20487
    int CSchedulingManagerView::sortCallback(LPARAM lParam1, LPARAM lParam2, int columnIndex, AutoSortListCtrl::ECurrentSort currentSort)
    {
        bool isAscend = (currentSort == AutoSortListCtrl::ASCENDING);
//      Job* job1 = reinterpret_cast<Job*>(isAscend ? lParam1 : lParam2);
//      Job* job2 = reinterpret_cast<Job*>(isAscend ? lParam2 : lParam1);
		Job* job1 = reinterpret_cast<Job*>( lParam1 );
		Job* job2 = reinterpret_cast<Job*>( lParam2 );
        TA_ASSERT(job1 != NULL, "Job 1 is NULL");
        TA_ASSERT(job2 != NULL, "Job 2 is NULL");

		int result = 0;
	
		switch (columnIndex)
        {
		case Status:
			result = compareStringContent( lParam1, lParam2, Status );
			if ( 0 == result )
			{
				result = compareStringContent( lParam1,lParam2, Location );
				if ( 0 == result )
				{
					result = compareStringContent( lParam1, lParam2, Type );
					if ( 0 == result )
					{
						result = m_pMainFrmModel->compareDateContent( job1, job2 );
					}
				}
			}
			break;
		case Type:
			result = compareStringContent( lParam1, lParam2, Type );
			if ( 0 == result )
			{
				result = compareStringContent( lParam1, lParam2, Location );
				if ( 0 == result )
				{
					result = compareStringContent( lParam1, lParam2, Status );
					if ( 0 == result )
					{
						result = m_pMainFrmModel->compareDateContent( job1, job2 );
					}
				}
			}
			break;
		case Description:
			result = compareStringContent( lParam1, lParam2 , Description );
			if ( 0 == result )
			{
				result = sortByPrimaryAndSecondary( lParam1, lParam2 );
				if ( 0 == result )
				{
					result = m_pMainFrmModel->compareDateContent( job1, job2 );
				}
			}
			break;
		case Profile:
			result = compareStringContent( lParam1, lParam2, Profile );
			if ( 0 == result )
			{
				result = sortByPrimaryAndSecondary( lParam1, lParam2 );
				if ( 0 == result )
				{
					result = m_pMainFrmModel->compareDateContent( job1, job2 );
				}
			}
			break;
		case Location:
			result = sortByPrimaryAndSecondary( lParam1, lParam2 );
			if ( 0 == result )
			{
				result = m_pMainFrmModel->compareDateContent( job1, job2 );
			}
			//return result;
			break;
        case Recurrence:
            {
                result =job1->getSchedule().getType() - job2->getSchedule().getType();
				if ( 0 == result )
				{
					result = sortByPrimaryAndSecondary( lParam1, lParam2 );
					if ( 0 == result )
					{
						result = m_pMainFrmModel->compareDateContent( job1, job2 );
					}
				}
                break;
            }
		case ScheduleEnd:
			
        case ScheduleStart:
            {
                COleDateTime* date1 = (columnIndex == ScheduleStart) ? job1->getStartDate() : job1->getSchedule().getEndDate();
                COleDateTime* date2 = (columnIndex == ScheduleStart) ? job2->getStartDate() : job2->getSchedule().getEndDate();

                // both dates are not specified
                if ((date1 == NULL) && (date2 == NULL))
                {
					// both equal
					result = sortByPrimaryAndSecondary( lParam1, lParam2 );
					if ( 0 == result )
					{
						result = m_pMainFrmModel->compareDateContent( job1, job2 );
					}

                }
                // both dates are specified
                else if ((date1 != NULL) && (date2 != NULL))
                {
                    if (*date1 == *date2)
                    {
						result = sortByPrimaryAndSecondary( lParam1, lParam2 );
						if ( 0 == result )
						{
							result = m_pMainFrmModel->compareDateContent( job1, job2 );
						}
                    }
                    else if (*date1 < *date2)
                    {
                        result = -1;
                    }
                    else
                    {
                        result = 1;
                    }
                }
                // only 1 date is specified
                else if (date1 != NULL)
                {
                    result = -1;
                }
                else // (date2 != NULL)
                {
                    result = 1;
                }

                // only need to delete if it is schedule end
                if (columnIndex == ScheduleEnd)
                {
                    delete date1;
                    delete date2;
                }
                
            }
			//return result;
			break;
        default:
            TA_ASSERT(false, "Only doing callbacks for dates and recurrence type");
        }


		switch (currentSort)
        {
        case AutoSortListCtrl::ASCENDING:
            return result;
        case AutoSortListCtrl::DESCENDING:
            return -result;
        default:
            ASSERT(FALSE);
            return result;
        }     


    }
	//++jinhua TD20487


    void CSchedulingManagerView::onFilePrint() 
    {
	    FUNCTION_ENTRY( "onFilePrint" );

		// TD #13511
		// Using the threaded printing (commented out, below) will
		// cause an assertion failure.
		// Could not find the cause, but this method works:
		CListCtrlPrint cJob;

		// Set the header information.
		CString header;

		TA_Base_Core::DateFormat dateFormat; 
		std::string dateFormatStr = dateFormat.getDateFormat(TA_Base_Core::DateFormat::DateTimeFormat4);

		AfxFormatString1(header, 
            m_isProfileFilterOn ? IDS_PROFILE_SCHEDULES_PRINT_HEADER : IDS_ALL_SCHEDULES_PRINT_HEADER, 
            CTime::GetCurrentTime().Format(dateFormatStr.c_str()));
		// ++ TD12474

		cJob.csPageHead = header;
		cJob.csPage = "Page %d of %d";

		int numCols = ((CHeaderCtrl*)(m_listCtrl.GetDlgItem(0)))->GetItemCount();
		TA_Base_Bus::CellColourMap colourMap( numCols, m_listCtrl.GetItemCount(), 0, m_listCtrl.GetBkColor() );
		cJob.pColourMap = &colourMap;
		//cl-16406-lkm
		if (m_printoutColWidths != NULL)
		{
			// create a new col width array for cJob to process the width, if there are changes
			cJob.pColWidthArray = m_printoutColWidths;
		}
		//cl-16406-lkm
		// Finally, add the list of data to print and then print it.
		cJob.pList = &m_listCtrl;
		cJob.OnFilePrint();

        FUNCTION_EXIT;
    }

	//TD16070++
	bool CSchedulingManagerView::canLoadDLL()
	{
		//this function is used only in adding job.
		//from JobDialog implementation, 
		//if the job is new, then just select the first job type by default
		Job job;
        for (unsigned int i = 0; i < m_jobTypes.size(); i++)
        {
            const std::string ALARM_GENERATOR_TYPE("AlarmGeneratorJob");
            if(m_jobTypes[i] == ALARM_GENERATOR_TYPE && job.getType() != ALARM_GENERATOR_TYPE)
            {
                continue;
            }
			else
			{
				job.setType(m_jobTypes[i].c_str()); 
				break;
			}
        }

        try
        {
			ComponentLibraryAccessor componentLibraryAccessor(m_jobTypes);
            IJobDetailsPlugin* plugin = componentLibraryAccessor.getComponent(job.getType());
            if (plugin != NULL)
            {
				return true;
            }
			else
			{
                TransActiveMessage userMsg;
                userMsg << job.getType().c_str();
                UINT selectedButton = userMsg.showMsgBox(IDS_UE_250013);
			}
        }
        catch (...)
        {
			TransActiveMessage userMsg;
            userMsg << job.getType().c_str();
            UINT selectedButton = userMsg.showMsgBox(IDS_UE_250013);
        }
		
		return false;
	}
	//++TD16070


	//jinhua++ TD20487
	int CSchedulingManagerView::compareStringContent( int rowIndex1, int rowIndex2, int columnIndex )
	{
		LVFINDINFO info;
		info.flags = LVFI_PARAM;
		info.lParam = rowIndex1;
		CString str1, str2;

		int index = -1;
		index = m_listCtrl.FindItem(&info);
		if (-1 == index)
		{
			return 0;
		}
		else
		{
			str1 = m_listCtrl.GetItemText( index, columnIndex );
        }
		
		index = -1;
		info.lParam = rowIndex2;
		index = m_listCtrl.FindItem( &info );
		if ( -1 == index )
		{
			return 0;
		}
		else 
		{
			str2 = m_listCtrl.GetItemText(index, columnIndex );
		}

		return str1.Compare( str2 );


	}

	int CSchedulingManagerView::sortByPrimaryAndSecondary( int rowIndex1, int rowIndex2 )
	{
		int result = 0;
		result = compareStringContent( rowIndex1, rowIndex2, Location );
		if ( 0 == result )
		{
			result = compareStringContent( rowIndex1, rowIndex2, Status );
			if ( 0 == result )
			{
				result = compareStringContent( rowIndex1, rowIndex2, Type );
			}
		}
		
		return result;		
	}
	//++jinhua TD20487

	JobPtrMap CSchedulingManagerView::getAllJobs()
	{
		FUNCTION_ENTRY( "getAllJobs" );
		TA_ASSERT(m_jobManager != NULL, "JobManager is NULL, cannot continue");
		if (m_isProfileFilterOn)
		{
			return m_jobManager->getAllJobsByProfile();
		}
		return m_jobManager->getAllJobs();
		FUNCTION_EXIT;
	}

	unsigned long CSchedulingManagerView::getJobCount()
	{
		FUNCTION_ENTRY( "getJobCount" );
		TA_ASSERT(m_jobManager != NULL, "JobManager is NULL, cannot continue");
		if (m_isProfileFilterOn)
		{
			return m_jobManager->getTotalJobCountByProfile();
		}
		return m_jobManager->getTotalJobCount();
		FUNCTION_EXIT;
	}

	void CSchedulingManagerView::onViewAlljobs() 
	{
		m_isProfileFilterOn = !m_isProfileFilterOn;
		//UpdateAllViews(NULL);
		OnUpdate(NULL,0L,NULL);
	}

	void CSchedulingManagerView::onUpdateViewAlljobs(CCmdUI* pCmdUI) 
	{
		pCmdUI->SetCheck(!m_isProfileFilterOn);
	}


	void CSchedulingManagerView::OnAppAbout() 
	{
		TA_Base_Bus::HelpLauncher::getInstance().displayAboutBox();
	}

	void CSchedulingManagerView::OnHelpSchedulingmanager() 
	{
		TA_Base_Bus::HelpLauncher::getInstance().displayHelp();
	}

	bool CSchedulingManagerView::getIsProfileFilterOn()
	{
		return m_isProfileFilterOn;
	}

	void CSchedulingManagerView::setMainFrameModel(MainFrameModel* pModel)
	{
        m_pMainFrmModel = pModel;
	}

	void CSchedulingManagerView::PostNcDestroy()
	{
		// TODO: Add your specialized code here and/or call the base class

		//CListView::PostNcDestroy();
	}

	LRESULT CSchedulingManagerView::OnSetLanguage(WPARAM wParam, LPARAM lParam)
	{
		CHeaderCtrl* pListHeader = m_listCtrl.GetHeaderCtrl();

		for (int i = 0; i < CSchedulingManagerView::NumColumnType; i++)
		{			
			HDITEM hditem;
			enum   { sizeOfBuffer = 256 };
			TCHAR  lpBuffer[sizeOfBuffer];

			hditem.mask = HDI_TEXT;
			hditem.pszText = lpBuffer;
			hditem.cchTextMax = sizeOfBuffer;

			TAUnicodeString columnName = TALoadString(COLUMN_INFO[i].name);
			//std::string strColumnName = columnName.toMultiByteStdString();
			pListHeader->GetItem(i, &hditem);
			hditem.pszText = (LPWSTR)columnName.GetString();
			pListHeader->SetItem(i, &hditem);
		}

		return TACListView::OnSetLanguage(wParam,lParam);
	}
};

