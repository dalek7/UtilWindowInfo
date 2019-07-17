
// TestWindowTitleView.h : interface of the CTestWindowTitleView class
//

#pragma once

#include "../lib/ddStatic.h"
#include "afxwin.h"
class CTestWindowTitleView : public CFormView
{
protected: // create from serialization only
	CTestWindowTitleView();
	DECLARE_DYNCREATE(CTestWindowTitleView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_TESTWINDOWTITLE_FORM };
#endif

// Attributes
public:
	CTestWindowTitleDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CTestWindowTitleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	ddStatic m_info1;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	ddStatic m_info2;
};

#ifndef _DEBUG  // debug version in TestWindowTitleView.cpp
inline CTestWindowTitleDoc* CTestWindowTitleView::GetDocument() const
   { return reinterpret_cast<CTestWindowTitleDoc*>(m_pDocument); }
#endif

