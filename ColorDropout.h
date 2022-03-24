// ColorDropout.h : main header file for the ColorDropout application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CColorDropoutApp:
// See ColorDropout.cpp for the implementation of this class
//

class CColorDropoutApp : public CWinApp
{
public:
	CColorDropoutApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileOpenimage();
};

extern CColorDropoutApp theApp;