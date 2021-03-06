/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/app/data_management/archive_manager/src/DateRangeDlg.cpp $
  * @author:  Alan Brims
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2015/10/09 15:42:35 $
  * Last modified by:  $Author: CM $
  *
  * Dialog for operator to select the range to be manually archived.
  */

#if defined( WIN32 )
#pragma warning ( disable : 4503 ) 
#endif // defined( WIN32 )

#include "app/data_management/archive_manager/src/stdafx.h"
#include "app/data_management/archive_manager/src/DateRangeDlg.h"
#include "bus/generic_gui_view/src/TransactiveMessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace TA_Base_App
{
    
    /////////////////////////////////////////////////////////////////////////////
    // DateRangeDlg dialog
    
    
    DateRangeDlg::DateRangeDlg(CWnd* pParent /*=NULL*/)
        : AbstractDialog(dynamic_cast<TA_Base_Bus::ITransActiveWinApp*> (AfxGetApp()),DateRangeDlg::IDD, pParent)
    {        
		m_dvdVolume = 4700;
        //{{AFX_DATA_INIT(DateRangeDlg)
	    m_fromDatePickerValue;
	    m_toDatePickerValue;
	    //}}AFX_DATA_INIT
    }
    
    
    void DateRangeDlg::DoDataExchange(CDataExchange* pDX)
    {
        AbstractDialog::DoDataExchange(pDX);
        //{{AFX_DATA_MAP(DateRangeDlg)
	    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FROM, m_fromDatePickerValue);
	    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TO, m_toDatePickerValue);
		//DDX_Text(pDX, IDC_DVDVOLUMEEDIT, m_dvdVolume); //yangguang TD16713
		DDV_MinMaxInt(pDX, m_dvdVolume, 500, 100000 );
	    //}}AFX_DATA_MAP
    }
    
    
    BEGIN_MESSAGE_MAP(DateRangeDlg, AbstractDialog)
        //{{AFX_MSG_MAP(DateRangeDlg)
        //}}AFX_MSG_MAP
    END_MESSAGE_MAP()
        
    /////////////////////////////////////////////////////////////////////////////
    // DateRangeDlg message handlers
    
    BOOL DateRangeDlg::OnInitDialog() 
    {
        AbstractDialog::OnInitDialog();
                
        //  Give this dialog its parent's icons.

        SetIcon( GetParent()->GetIcon( true ), TRUE );			// Set big icon
        SetIcon( GetParent()->GetIcon( false ), FALSE );		// Set small icon

        //  Display an hour-glass cursor.

        HCURSOR hOldCursor = SetCursor( LoadCursor( NULL, IDC_APPSTARTING ) );

        // Select yesterday in both the date pickers.

        m_fromDatePickerValue = m_realPModel->getFromDate();
        m_toDatePickerValue = m_realPModel->getToDate();
        UpdateData( false);
        
        return TRUE;  // return TRUE unless you set the focus to a control
        // EXCEPTION: OCX Property Pages should return FALSE
    }
    
    void DateRangeDlg::OnOK() 
    {
        if(!UpdateData(true))
		{
			return ;
		}
        
        // KT 25 Mar 04: Use COleDateTime instead of CTime - this goes for longer (up to 9999).
        
        //  Convert date/times to just dates
        
        COleDateTime today( COleDateTime::GetCurrentTime() );
        today = COleDateTime( today.GetYear(), today.GetMonth(), today.GetDay(), 0,0,0 );
        m_fromDatePickerValue = COleDateTime( m_fromDatePickerValue.GetYear(), m_fromDatePickerValue.GetMonth(), m_fromDatePickerValue.GetDay(), 0,0,0 );
        m_toDatePickerValue = COleDateTime( m_toDatePickerValue.GetYear(), m_toDatePickerValue.GetMonth(), m_toDatePickerValue.GetDay(), 0,0,0 );
     
		

        if ( m_toDatePickerValue >= today )
        {
            TA_Base_Bus::TransActiveMessage userMsg;
            UINT selectedButton = userMsg.showMsgBox(IDS_UW_050009);
            GetDlgItem( IDC_DATETIMEPICKER_TO )->SetFocus();
            return;
        }
        
        if (m_fromDatePickerValue > m_toDatePickerValue)
        {
            TA_Base_Bus::TransActiveMessage userMsg;
            UINT selectedButton = userMsg.showMsgBox(IDS_UW_050010);
			GetDlgItem( IDC_DATETIMEPICKER_FROM )->SetFocus();
            return;
        }

        //
        // Merged from CODE_4619 for TD 11181
        //
		// TD #10595
		// Archive Manager was crashing if 'from' and/or 'to' dates were set on or before
		// 01/01/1970. Check that the year is greater than 1970.
		// Technically, any date in 1970 other than 01/01 will not crash it, but here we
		// disallow all of 1970 for a simpler condition, seeing as not being albe to archive
		// data from 1970 should not be an issue anyway.
		// Note that only the 'from' date needs to be checked, since we know the 'to' date
		// is already greter than this.
        if (m_fromDatePickerValue.GetYear() <= 1970)
        {
            TA_Base_Bus::TransActiveMessage userMsg;
			UINT selectedButton = userMsg.showMsgBox(IDS_UE_050143);
            GetDlgItem( IDC_DATETIMEPICKER_FROM )->SetFocus();
            return;
        }

        // Need to set these, so they can be used in ArchiveManagerDlg.
		m_realPModel->setSelectedDataDateRange(TA_ArchiveManager::convertCOleDateTimeToTimeT( m_fromDatePickerValue ),
			TA_ArchiveManager::convertCOleDateTimeToTimeT( m_toDatePickerValue ),m_dvdVolume);

        AbstractDialog::OnOK();
    }

	///////////////////////////////////////////////////////////////////////////////////////////
	/// AbstractTransActiveView member functions

	std::string DateRangeDlg::getMyPModelName()
	{
		return WRITE_ARCHIVE_DLG_PMODEL;
	}

	void DateRangeDlg::setupPModel()
	{
		m_realPModel = dynamic_cast<WriteArchivePModel*> (m_pModel);
		TA_ASSERT(m_realPModel != NULL, "PModel has been initialized successfully");
	}

	void DateRangeDlg::notifyUpdate(const char * updateType, TA_Base_Bus::EventArgs * args)
	{
	}
    
} // TA_Base_App
