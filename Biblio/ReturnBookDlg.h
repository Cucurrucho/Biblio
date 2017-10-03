#pragma once
#include "MyDialogEx.h"

// CReturnBookDlg dialog

class CReturnBookDlg : public CMyDialogEx
{
	DECLARE_DYNAMIC(CReturnBookDlg)

public:
	CReturnBookDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CReturnBookDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RETURN_BOOK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSearchLending();
};
