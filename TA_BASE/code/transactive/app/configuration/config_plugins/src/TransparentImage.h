/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/app/configuration/config_plugins/src/TransparentImage.h $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2015/10/09 15:42:35 $
  * Last modified by:  $Author: CM $
  *
  */
#ifndef __TRANSPARENTIMAGE_H_TRANSPARENTIMAGE_42A6E395_97E4_11D3_B6F0_005004024A9E
#define __TRANSPARENTIMAGE_H_TRANSPARENTIMAGE_42A6E395_97E4_11D3_B6F0_005004024A9E

#if _MSC_VER >= 1000
#pragma once
#endif

class CTransparentImage 
	: public CStatic
{
	public:

	CTransparentImage() ;

	virtual ~CTransparentImage() ;
	//
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	// ClassWizard generated virtual function overrides
	//
	//{{AFX_VIRTUAL( CTransparentImage )
	//}}AFX_VIRTUAL
	//
	////////////////////////////////////////////////////////////////////////////
	protected:
	//
	//{{AFX_MSG( CTransparentImage )
	afx_msg void OnPaint() ;
	//}}AFX_MSG
	//
	DECLARE_MESSAGE_MAP()
	//
	////////////////////////////////////////////////////////////////////////////
} ;

//{{AFX_INSERT_LOCATION}}

#endif
