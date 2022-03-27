// ProcessDialog.cpp : implementation file
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
#include "ProcessDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProcessDialog dialog


CProcessDialog::CProcessDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CProcessDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProcessDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CProcessDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProcessDialog)
	DDX_Control(pDX, IDC_PROCESS_LIST, m_Process_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProcessDialog, CDialog)
	//{{AFX_MSG_MAP(CProcessDialog)
	ON_LBN_DBLCLK(IDC_PROCESS_LIST, OnDblclkProcessList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProcessDialog message handlers

void CProcessDialog::OnOK() 
{
    // Return the thread ID
    m_dwProcessId = m_Process_List.GetItemData(m_Process_List.GetCurSel());
	m_Process_List.GetText(m_Process_List.GetCurSel(), m_sProcessName);

	CDialog::OnOK();
}

BOOL CProcessDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//
    // Popoluate the process list
    //
	CreateProcessList();

    // Select the first entry
    m_Process_List.SetCurSel(0);
    m_Process_List.SetFocus();

    UpdateData(FALSE);

	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CProcessDialog::CreateProcessList()
{
    HANDLE  hProcess;
    DWORD   dwPIDArray[1024];
    DWORD   dwPIDArraySize = sizeof(dwPIDArray);
    DWORD   dwPIDBytesReturned = 0;

    HMODULE hModuleArray[512];
    DWORD   dwModuleArraySize = sizeof(hModuleArray);
    DWORD   dwModuleBytesReturned = 0;
    ULONG   i;

    CHAR    sBaseName[256];
    DWORD   dwBaseNameSize = sizeof(sBaseName);

    CString sOurName;
    CString sOtherNames;

    BOOL    bRtn;
    DWORD   dwRtn;

    CString sTemp;

    DWORD   dwListIndex = 0;

    //
    // Obtain the process ID list
    //
    bRtn = ::EnumProcesses(dwPIDArray, dwPIDArraySize, &dwPIDBytesReturned);

    //
    // Get the process handles from the Process ID. 
    // Obtain the modules used by the process and their names
    //
    for (i=0; i<dwPIDBytesReturned/sizeof(DWORD); i++) 
    {
        hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwPIDArray[i]);
        if (hProcess != NULL) {
            bRtn = ::EnumProcessModules(hProcess, hModuleArray, dwModuleArraySize, &dwModuleBytesReturned);
            // Index 0 is the EXE (process) name, Index 1...x are the import DLL's
            dwRtn = ::GetModuleBaseName(hProcess, hModuleArray[0], sBaseName, dwBaseNameSize);
            if (dwRtn > 0)
            {
                sTemp.Format("%s    (pid %u)", sBaseName, dwPIDArray[i]);
                dwListIndex = m_Process_List.AddString(sTemp);
                m_Process_List.SetItemData(dwListIndex, dwPIDArray[i]);
            }
            ::CloseHandle(hProcess);
        }
    }

    return;
}

void CProcessDialog::OnDblclkProcessList() 
{
    // Pass it to the standard OK handler
    CProcessDialog::OnOK();
}
