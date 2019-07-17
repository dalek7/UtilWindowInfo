
// TestWindowTitleView.cpp : implementation of the CTestWindowTitleView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "TestWindowTitle.h"
#endif

#include "TestWindowTitleDoc.h"
#include "TestWindowTitleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestWindowTitleView

IMPLEMENT_DYNCREATE(CTestWindowTitleView, CFormView)

BEGIN_MESSAGE_MAP(CTestWindowTitleView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CTestWindowTitleView::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CTestWindowTitleView construction/destruction

CTestWindowTitleView::CTestWindowTitleView()
	: CFormView(IDD_TESTWINDOWTITLE_FORM)
{
	// TODO: add construction code here

}

CTestWindowTitleView::~CTestWindowTitleView()
{
}

void CTestWindowTitleView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_info1);
	DDX_Control(pDX, IDC_STATIC2, m_info2);
}

BOOL CTestWindowTitleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CTestWindowTitleView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	SetTimer(0, 100, NULL);

}


// CTestWindowTitleView diagnostics

#ifdef _DEBUG
void CTestWindowTitleView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTestWindowTitleView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTestWindowTitleDoc* CTestWindowTitleView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestWindowTitleDoc)));
	return (CTestWindowTitleDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestWindowTitleView message handlers


void CTestWindowTitleView::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	m_info1.SetWindowTextW(L"aa");
	CPoint pt1;
	m_info1.GetCursorPtInObjCoord(&pt1);

	char buf[255];
	sprintf_s(buf, "%d, %d", pt1.x, pt1.y);

	CStringW str1(buf);
	m_info1.SetWindowTextW(str1);
}

// TODO : clean-up 

#include <psapi.h> // For access to GetModuleFileNameEx
void CTestWindowTitleView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 0)
	{
		CPoint pt1;
		GetCursorPos(&pt1);

		CWnd *p = WindowFromPoint(POINT(pt1));

		int length = 256; //SendMessage(hwnd,WM_GETTEXTLENGTH,0,0);

		//wchar_t* buffer = new wchar_t[length + 1];
		
		wchar_t buf_title[MAX_PATH] = { 0 };
		p->GetWindowTextW(buf_title, MAX_PATH);

		// process id
		DWORD processId;
		GetWindowThreadProcessId(p->m_hWnd, &processId);
		

		HANDLE processHandle = NULL;
		TCHAR filename[MAX_PATH];
		CStringW message1;
		processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);

		if (processHandle != NULL) {
			if (GetModuleFileNameEx(processHandle, NULL, filename, MAX_PATH) == 0) {
				;
				//tcerr << "Failed to get module filename." << endl;
				message1 = L"Failed to get module filename.";
			}
			else {
				;
				//tcout << "Module filename is: " << filename << endl;
				message1 = filename;
			}
			CloseHandle(processHandle);
		}
		else {
			//tcerr << "Failed to open process." << endl;
			message1 = L"Failed to open process";
		}

		char buf[255];
		sprintf_s(buf, "(%d, %d)\tPID:%d\t", pt1.x, pt1.y, processId);

		CStringW str1(buf);
		CStringW str2(buf_title);

		m_info1.SetWindowTextW(str1 + str2);
		m_info2.SetWindowTextW(message1);

	}
	CFormView::OnTimer(nIDEvent);
}


void CTestWindowTitleView::OnDestroy()
{
	CFormView::OnDestroy();

	KillTimer(0);
	// TODO: Add your message handler code here
}
