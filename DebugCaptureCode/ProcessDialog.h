#if !defined(AFX_PROCESSDIALOG_H__0FC05540_DFFA_4AA2_B844_7AC12A25C0A2__INCLUDED_)
#define AFX_PROCESSDIALOG_H__0FC05540_DFFA_4AA2_B844_7AC12A25C0A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProcessDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProcessDialog dialog

class CProcessDialog : public CDialog
{
// Construction
public:
	CString m_sProcessName;
	DWORD_PTR m_dwProcessId;
	CProcessDialog(CWnd* pParent = NULL);   // standard constructor

    void CreateProcessList();

// Dialog Data
	//{{AFX_DATA(CProcessDialog)
	enum { IDD = IDD_PROCESS_DIALOG };
	CListBox	m_Process_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProcessDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProcessDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkProcessList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROCESSDIALOG_H__0FC05540_DFFA_4AA2_B844_7AC12A25C0A2__INCLUDED_)
