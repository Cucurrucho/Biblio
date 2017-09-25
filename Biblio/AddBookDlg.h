#pragma once
#include "MyDialogEx.h"


// CAddBookDlg dialog

class CAddBookDlg : public CMyDialogEx
{
	DECLARE_DYNAMIC(CAddBookDlg)

public:
	CAddBookDlg(class CBook &book, CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddBookDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_BOOK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	class CBook &mBook;
	virtual void OnOK();
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButtonBuscar();
};
