
// TestWindowTitle.h : main header file for the TestWindowTitle application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CTestWindowTitleApp:
// See TestWindowTitle.cpp for the implementation of this class
//

class CTestWindowTitleApp : public CWinApp
{
public:
	CTestWindowTitleApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTestWindowTitleApp theApp;
