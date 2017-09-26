
// BiblioDlg.h : header file
//

#pragma once


// CBiblioDlg dialog
class CBiblioDlg : public CDialogEx
{
// Construction
public:
	CBiblioDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BIBLIO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileExit();
	afx_msg void OnBooksAdd();
	afx_msg void OnDatabaseInit();
	afx_msg void OnSociosAgregar();
	afx_msg void OnClientSearch();
};
