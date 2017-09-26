#pragma once
#include "MyDialogEx.h"

// CLendDlg dialog

class CLendDlg : public CMyDialogEx
{
	DECLARE_DYNAMIC(CLendDlg)

public:
	CLendDlg(class CBook &book, class CSocio &socio, CWnd* pParent = NULL);   // standard constructor
	virtual ~CLendDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LEND_BOOK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	class CBook &mBook;
	class CSocio &mSocio;
	virtual void OnOK();
};
