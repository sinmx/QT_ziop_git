/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/app/response_plans/plan_manager/prototype/src/BlankForm.cpp $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2015/10/09 15:42:35 $
  * Last modified by:  $Author: CM $
  *
  */
// BlankForm.cpp : implementation file
//

#include "stdafx.h"
#include "PlanViewer.h"
#include "BlankForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBlankForm

IMPLEMENT_DYNCREATE(CBlankForm, CFormView)

CBlankForm::CBlankForm()
    : CFormView(CBlankForm::IDD)
{
    FUNCTION_ENTRY( "CBlankForm" );

    // {{AFX_DATA_INIT(CBlankForm)
        // NOTE: the ClassWizard will add member initialization here
    // }}AFX_DATA_INIT

    FUNCTION_EXIT;
}


CBlankForm::~CBlankForm()
{
    FUNCTION_ENTRY( "~CBlankForm" );
    FUNCTION_EXIT;
}


void CBlankForm::DoDataExchange(CDataExchange* pDX)
{
    FUNCTION_ENTRY( "DoDataExchange" );

    CFormView::DoDataExchange(pDX);
    // {{AFX_DATA_MAP(CBlankForm)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    // }}AFX_DATA_MAP

    FUNCTION_EXIT;
}


BEGIN_MESSAGE_MAP(CBlankForm, CFormView)
    // {{AFX_MSG_MAP(CBlankForm)
    ON_WM_CREATE()
    // }}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlankForm diagnostics

#ifdef _DEBUG
void CBlankForm::AssertValid() const
{
    FUNCTION_ENTRY( "AssertValid" );

    CFormView::AssertValid();

    FUNCTION_EXIT;
}


void CBlankForm::Dump(CDumpContext& dc) const
{
    FUNCTION_ENTRY( "Dump" );

    CFormView::Dump(dc);

    FUNCTION_EXIT;
}


#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBlankForm message handlers

int CBlankForm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    FUNCTION_ENTRY( "OnCreate" );

    if (CFormView::OnCreate(lpCreateStruct) == -1)
    {
        FUNCTION_EXIT;
        return -1;
    }

    FUNCTION_EXIT;
    return 0;
}


