// Transform.h : main header file for the TRANSFORM application
//

#if !defined(AFX_TRANSFORM_H__D36E1E58_F064_410C_B170_583C43569E1D__INCLUDED_)
#define AFX_TRANSFORM_H__D36E1E58_F064_410C_B170_583C43569E1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTransformApp:
// See Transform.cpp for the implementation of this class
//

class CTransformApp : public CWinApp
{
public:
	CTransformApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransformApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTransformApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSFORM_H__D36E1E58_F064_410C_B170_583C43569E1D__INCLUDED_)
