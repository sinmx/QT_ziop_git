/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/bus/mfc_extensions/src/tab_control_with_disable/TabCtrlWithDisable.cpp $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2015/10/09 15:42:35 $
  * Last modified by:  $Author: CM $
  *
  */
////////////////////////////////////////////////////////////////
// CTabCtrlWithDisable 1998 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// CTabCtrlWithDisable implements a CTabCtrl with tabs that you can disable.

#include "../StdAfx.h"
#include "TabCtrlWithDisable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CTabCtrlWithDisable, CTabCtrl)
BEGIN_MESSAGE_MAP(CTabCtrlWithDisable, CTabCtrl)
   ON_NOTIFY_REFLECT_EX(TCN_SELCHANGING, OnSelChanging)
END_MESSAGE_MAP()

CTabCtrlWithDisable::CTabCtrlWithDisable()
{
}

CTabCtrlWithDisable::~CTabCtrlWithDisable()
{
}

//////////////////
// Subclass the tab control: also make owner-draw
// 
BOOL CTabCtrlWithDisable::SubclassDlgItem(UINT nID, CWnd* pParent)
{
   if (!CTabCtrl::SubclassDlgItem(nID, pParent))
      return FALSE;

   ModifyStyle(0, TCS_OWNERDRAWFIXED);

   // If first tab is disabled, go to next enabled tab
   if (!IsTabEnabled(0)) {
      int iTab = NextEnabledTab(0, TRUE);
      SetActiveTab(iTab);
   }
   return TRUE;
}

//////////////////
// Draw the tab: mimic SysTabControl32, except use gray if tab is disabled
//
void CTabCtrlWithDisable::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
   DRAWITEMSTRUCT& ds = *lpDrawItemStruct;
   
   int iItem = ds.itemID;

   // Get tab item info
   TCHAR text[128];
   TCITEM tci;
   tci.mask = TCIF_TEXT;
   tci.pszText = text;
   tci.cchTextMax = sizeof(text);
   GetItem(iItem, &tci);

   // use draw item DC
   CDC dc;
   dc.Attach(ds.hDC);

   // draw text background
   CRect bkRc = ds.rcItem;
   bkRc.top += ::GetSystemMetrics(SM_CYEDGE);
   dc.SetBkMode(TRANSPARENT);
   dc.FillSolidRect(bkRc, ::GetSysColor(COLOR_BTNFACE));

   // calculate text rectangle
   CRect rc = ds.rcItem;
   rc += CPoint(0,3);
       
   // draw the text
   OnDrawText(dc, rc, text, !IsTabEnabled(iItem));

   dc.Detach();
}

//////////////////
// Draw tab text. You can override to use different color/font.
//
void CTabCtrlWithDisable::OnDrawText(CDC& dc, CRect rc,
   CString sText, BOOL bDisabled)
{
    if (bDisabled)
    {
        // Create a shadow effect by first drawing the text in light highlight colour
        // at a slight south-east offset.
        CRect shadowRc(rc);
        shadowRc += CPoint(1,1);
        dc.SetTextColor(::GetSysColor(COLOR_3DHILIGHT));
        dc.DrawText(sText, &shadowRc, DT_CENTER | DT_VCENTER);
    }

    // Draw the text in normal or disabled text colour
    dc.SetTextColor(::GetSysColor(bDisabled? COLOR_GRAYTEXT : COLOR_BTNTEXT));
    dc.DrawText(sText, &rc, DT_CENTER | DT_VCENTER);
}

//////////////////
// Selection is changing: disallow if tab is disabled
//
BOOL CTabCtrlWithDisable::OnSelChanging(NMHDR* pnmh, LRESULT* pRes)
{
   // Figure out index of new tab we are about to go to, as opposed
   // to the current one we're at. Believe it or not, Windows doesn't
   // pass this info
   //
   TC_HITTESTINFO htinfo;
   GetCursorPos(&htinfo.pt);
   ScreenToClient(&htinfo.pt);
   int iNewTab = HitTest(&htinfo);

   if (iNewTab >= 0 && !IsTabEnabled(iNewTab))
   {
      *pRes = TRUE; // tab disabled: prevent selection
      return TRUE;
   }

   return FALSE; // TD#2621: For a subclassed tab control that belongs to a property sheet, tab selection 
                 // change notification must be routed via the property sheet so that it can keep its pages 
                 // informed about their activation or deactivation.
}

//////////////////
// Trap arrow-left key to skip disabled tabs.
// This is the only way to know where we're coming from--ie from
// arrow-left (prev) or arrow-right (next).
//
BOOL CTabCtrlWithDisable::PreTranslateMessage(MSG* pMsg)
{
   if (pMsg->message == WM_KEYDOWN &&
      (pMsg->wParam == VK_LEFT || pMsg->wParam == VK_RIGHT)) {

      int iNewTab = (pMsg->wParam == VK_LEFT) ?
         PrevEnabledTab(GetCurSel(), FALSE) :
         NextEnabledTab(GetCurSel(), FALSE);
      if (iNewTab >= 0)
         SetActiveTab(iNewTab);
      return TRUE;
   }
   return CTabCtrl::PreTranslateMessage(pMsg);
}

////////////////
// Translate parent property sheet message. Translates Control-Tab and
// Control-Shift-Tab keys. These are normally handled by the property
// sheet, so you must call this function from your prop sheet's
// PreTranslateMessage function.
//
BOOL CTabCtrlWithDisable::TranslatePropSheetMsg(MSG* pMsg)
{
   WPARAM key = pMsg->wParam;
   if (pMsg->message == WM_KEYDOWN && GetAsyncKeyState(VK_CONTROL) < 0 &&
      (key == VK_TAB || key == VK_PRIOR || key == VK_NEXT)) {

      int iNewTab = (key==VK_PRIOR || GetAsyncKeyState(VK_SHIFT) < 0) ?
         PrevEnabledTab(GetCurSel(), TRUE) :
         NextEnabledTab(GetCurSel(), TRUE);
      if (iNewTab >= 0)
         SetActiveTab(iNewTab);
      return TRUE;
   }
   return FALSE;
}

//////////////////
// Helper to set the active page, when moving backwards (left-arrow and
// Control-Shift-Tab). Must simulate Windows messages to tell parent I
// am changing the tab; SetCurSel does not do this!!
//
// In normal operation, this fn will always succeed, because I don't call it
// unless I already know IsTabEnabled() = TRUE; but if you call SetActiveTab
// with a random value, it could fail.
//
BOOL CTabCtrlWithDisable::SetActiveTab(UINT iNewTab)
{
   // send the parent TCN_SELCHANGING
   NMHDR nmh;
   nmh.hwndFrom = m_hWnd;
   nmh.idFrom = GetDlgCtrlID();
   nmh.code = TCN_SELCHANGING;

   if (GetParent()->SendMessage(WM_NOTIFY, nmh.idFrom, (LPARAM)&nmh) >=0) {
      // OK to change: set the new tab
      SetCurSel(iNewTab);

      // send parent TCN_SELCHANGE
      nmh.code = TCN_SELCHANGE;
      GetParent()->SendMessage(WM_NOTIFY, nmh.idFrom, (LPARAM)&nmh);
      return TRUE;
   }
   return FALSE;
}

/////////////////
// Return the index of the next enabled tab after a given index, or -1 if none
// (0 = first tab).
// If bWrap is TRUE, wrap from beginning to end; otherwise stop at zero.
//
int CTabCtrlWithDisable::NextEnabledTab(int iCurrentTab, BOOL bWrap)
{
   int nTabs = GetItemCount();
   for (int iTab = iCurrentTab+1; iTab != iCurrentTab; iTab++) {
      if (iTab >= nTabs) {
         if (!bWrap)
            return -1;
         iTab = 0;
      }
      if (IsTabEnabled(iTab)) {
         return iTab;
      }
   }
   return -1;
}

/////////////////
// Return the index of the previous enabled tab before a given index, or -1.
// (0 = first tab).
// If bWrap is TRUE, wrap from beginning to end; otherwise stop at zero.
//
int CTabCtrlWithDisable::PrevEnabledTab(int iCurrentTab, BOOL bWrap)
{
   for (int iTab = iCurrentTab-1; iTab != iCurrentTab; iTab--) {
      if (iTab < 0) {
         if (!bWrap)
            return -1;
         iTab = GetItemCount() - 1;
      }
      if (IsTabEnabled(iTab)) {
         return iTab;
      }
   }
   return -1;
}