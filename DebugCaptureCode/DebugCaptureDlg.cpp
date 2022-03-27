// DebugCaptureDlg.cpp : implementation file
//
/*
BSD 3-Clause License

Copyright (c) 2022, Anthony Kempka
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "stdafx.h"
#include "DebugCapture.h"
#include "DebugCaptureDlg.h"

#include "ProcessDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDebugCaptureDlg dialog

CDebugCaptureDlg::CDebugCaptureDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDebugCaptureDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDebugCaptureDlg)
	m_sDebug_Output = _T("");
	m_sProcess_Name = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDebugCaptureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDebugCaptureDlg)
	DDX_Text(pDX, IDC_DEBUG_OUTPUT, m_sDebug_Output);
	DDX_Text(pDX, IDC_PROCESS_NAME, m_sProcess_Name);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDebugCaptureDlg, CDialog)
	//{{AFX_MSG_MAP(CDebugCaptureDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PROCESS_BUTTON, OnProcessButton)
	ON_BN_CLICKED(IDC_CAPTURE_BUTTON, OnCaptureButton)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


///////////////////////////////////////////////////////////////////////////////////////////////////
// DisplayErrors
//
// Prints the formatted text string for a given WINERROR error code
//
// Parameters
// ----------
// sErrorDescription    Used in printing the formatted error string
// dwError              Error code returned by ::GetLastError()
//
void  CDebugCaptureDlg::DisplayErrors(LPSTR sErrorDescription, DWORD dwError)
{
    CString sError;
    LPVOID  lpMsgBuf;
    FormatMessage( 
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM | 
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dwError,
        0, // Default language
        (LPTSTR)&lpMsgBuf,
        0,
        NULL);

    // Process any inserts in lpMsgBuf.
    // ...

    // Display the string.
    sError.Format("%s Code(%u) %s\n", sErrorDescription, dwError, lpMsgBuf);

    AfxMessageBox(sError, MB_ICONERROR);

    // Free the buffer.
    LocalFree( lpMsgBuf );

    return;
}


/////////////////////////////////////////////////////////////////////////////
// CDebugCaptureDlg message handlers

BOOL CDebugCaptureDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
    m_bCapturing = FALSE;
    m_bWaitingToExit = FALSE;
    m_dwProcessId = 0;
    m_hProcess = NULL;
    m_sProcess_Name = "No process selected";
    UpdateData(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDebugCaptureDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDebugCaptureDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDebugCaptureDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CDebugCaptureDlg::OnCancel() 
{
    // If capturing debug on a process, stop the capture
    if (m_bCapturing) {
        Stop_Capture();
        // ShowWindow(SW_HIDE);
        //m_bWaitingToExit = TRUE;
        //return;
    }
	CDialog::OnCancel();
}


void CDebugCaptureDlg::OnProcessButton() 
{
    CProcessDialog  dlg;

   	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
        m_dwProcessId = dlg.m_dwProcessId;
        m_sProcess_Name = dlg.m_sProcessName;

        UpdateData(FALSE);
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is dismissed with Cancel
	}
    return;	
}


void CDebugCaptureDlg::OnCaptureButton() 
{
    CButton* pButton;
    pButton = (CButton*)GetDlgItem(IDC_CAPTURE_BUTTON);

    if (!m_bCapturing) 
    {
        // Attach to process and begin capture

        if (Start_Capture()) {
            pButton->SetWindowText("Stop Capture");
            // Disable the button
            // pButton->EnableWindow(FALSE);
        }
    }
    else {
        Stop_Capture();
        pButton->SetWindowText("Start Capture");
    }
	return;
}


void CDebugCaptureDlg::Stop_Capture()
{
    if (m_bCapturing)
    {
        m_bCapturing = FALSE;
        KillTimer(1);
        if (m_dwProcessId != 0)
        {
            ::DebugActiveProcessStop((DWORD)m_dwProcessId);
        }
    }
}


BOOL CDebugCaptureDlg::Start_Capture()
{
    CString sTemp;
    BOOL    bRtn;

    // Bail if a process ID is not selected
    if (m_dwProcessId == 0)
    {
        DisplayErrors("No process selected.", ERROR_INVALID_FUNCTION);
        return(FALSE);
    }
        
    if (m_hProcess == NULL)
        m_hProcess = ::OpenProcess(PROCESS_VM_READ | SYNCHRONIZE | PROCESS_TERMINATE, TRUE, (DWORD)m_dwProcessId);

    if (m_hProcess == NULL) {

        DisplayErrors("Cannot open process.", ::GetLastError());
        m_bCapturing = FALSE;
        return (FALSE);
    }

    // Start to debug the process
    if (!::DebugActiveProcess((DWORD)m_dwProcessId)) {
        DisplayErrors("Cannot debug process.", ::GetLastError());
        m_bCapturing = FALSE;
        bRtn = FALSE;
    } else {
        sTemp.Format("Starting to capture debug output for process %s\r\n", m_sProcess_Name.GetBuffer());
        m_sDebug_Output += sTemp;
        m_bCapturing = TRUE;
        bRtn = TRUE;
        SetTimer(1, 100, NULL);
    }
    UpdateData(FALSE);

    return (bRtn);
}


void CDebugCaptureDlg::OnTimer(UINT_PTR nIDEvent) 
{
    CWaitCursor cWait;
    CString     sTemp;
    CHAR        sDebugString[1024];
    PCHAR       pEventString;
    DEBUG_EVENT Evnt;
    DWORD       dwCount;
    SIZE_T      dwBytesRead;
    DWORD       dwContinueStatus = DBG_CONTINUE;
    DWORD       dwDebugEventCount = 0;

    // Is this our timer?
    if (nIDEvent == 1) {
        // See if there are any debug events. 0 wait time will immediately return
        while (::WaitForDebugEvent(&Evnt, 0)) {
            switch (Evnt.dwDebugEventCode) 
            {
            case OUTPUT_DEBUG_STRING_EVENT:
                dwDebugEventCount++;
                ::ZeroMemory(sDebugString, sizeof(sDebugString));
                dwCount = Evnt.u.DebugString.nDebugStringLength;
                // Limit the debug string to 1024 chars (need trailing /0)
                if (dwCount > 1023) 
                    dwCount = 1023;
                pEventString = Evnt.u.DebugString.lpDebugStringData;
                ::ReadProcessMemory(m_hProcess, pEventString, sDebugString, dwCount, &dwBytesRead);
                sTemp.Format(": %s\r\n", sDebugString);
                m_sDebug_Output += sTemp;
                break;

            case EXIT_PROCESS_DEBUG_EVENT:
                sTemp.Format("Exit process event\r\n");
                m_sDebug_Output += sTemp;
                // BUGBUG: delete this since it's OBE
                if (m_bWaitingToExit) {
                    Stop_Capture();
                }
                break;
            default:
                // Some interesting things to see if you enable this code.
                // 
                // sTemp.Format("Unhandled code %u for process ID %u\r\n", Evnt.dwDebugEventCode, Evnt.dwProcessId);
                // m_sDebug_Output += sTemp;
                break;
            }
            ::ContinueDebugEvent(Evnt.dwProcessId, Evnt.dwThreadId, dwContinueStatus);
        }

        if (dwDebugEventCount != 0)
        {
            CEdit* pEdit;
            UpdateData(FALSE);
            pEdit = (CEdit*)GetDlgItem(IDC_DEBUG_OUTPUT);
            // Move the scroll bar to the end
            pEdit->LineScroll(pEdit->GetLineCount());
        }
            
    }
    // Forward to base class handler
	CDialog::OnTimer(nIDEvent);
}
