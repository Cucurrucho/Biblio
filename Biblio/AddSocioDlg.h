#pragma once
#include "MyDialogEx.h"
#include "afxdtctl.h"


// CAddSocioDlg dialog

class CAddSocioDlg : public CMyDialogEx
{
	DECLARE_DYNAMIC(CAddSocioDlg)

public:
	CAddSocioDlg(class CSocio &socio, CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddSocioDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_SOCIO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	class CSocio &mSocio;
	virtual void OnOK();
	CDateTimeCtrl mDTPicker;
	afx_msg void OnDtnDatetimechangeIngreso(NMHDR *pNMHDR, LRESULT *pResult);
};
