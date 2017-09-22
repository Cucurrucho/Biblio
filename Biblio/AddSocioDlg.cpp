// AddSocioDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Biblio.h"
#include "AddSocioDlg.h"
#include "afxdialogex.h"
#include "Socio.h"


// CAddSocioDlg dialog

IMPLEMENT_DYNAMIC(CAddSocioDlg, CDialogEx)

CAddSocioDlg::CAddSocioDlg(CSocio &socio, CWnd* pParent /*=NULL*/)
	: CMyDialogEx(IDD_ADD_SOCIO, pParent)
	, mSocio(socio)
{

}

CAddSocioDlg::~CAddSocioDlg()
{
}

void CAddSocioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INGRESO, mDTPicker);
}

void CAddSocioDlg::OnOK() {
	CWnd *pWnd = GetDlgItem(IDC_EDIT_NOMBRE);
	if (pWnd)
		pWnd->GetWindowText(mSocio.mNombre);
	pWnd = GetDlgItem(IDC_EDIT_DNI);
	if (pWnd)
		pWnd->GetWindowText(mSocio.mDNI);
	pWnd = GetDlgItem(IDC_EDIT_MAIL);
	if (pWnd)
		pWnd->GetWindowText(mSocio.mMail);
	pWnd = GetDlgItem(IDC_EDIT_TELEFONO);
	if (pWnd)
		pWnd->GetWindowText(mSocio.mTelefono);
	pWnd = GetDlgItem(IDC_EDIT_DOMICILIO);
	if (pWnd)
		pWnd->GetWindowText(mSocio.mDomicilio);
	if (mSocio.IsValid())
		CDialogEx::OnOK();
	else
	{
		MessageBox("Por favor llenar el campo Nombre", "Faltan Campos");
	}
}


BEGIN_MESSAGE_MAP(CAddSocioDlg, CDialogEx)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_INGRESO, &CAddSocioDlg::OnDtnDatetimechangeIngreso)
END_MESSAGE_MAP()


// CAddSocioDlg message handlers


void CAddSocioDlg::OnDtnDatetimechangeIngreso(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	GetDlgItemText(IDC_INGRESO, mSocio.mIngreso);
	UpdateData(FALSE);
	*pResult = 0;
}
