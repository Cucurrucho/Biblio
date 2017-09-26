// LendDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Biblio.h"
#include "LendDlg.h"
#include "afxdialogex.h"
#include "Book.h"
#include "Socio.h"


// CLendDlg dialog

IMPLEMENT_DYNAMIC(CLendDlg, CDialogEx)

CLendDlg::CLendDlg(CBook &book, CSocio &socio,CWnd* pParent /*=NULL*/)
	: CMyDialogEx(IDD_LEND_BOOK, pParent)
	, mBook(book)
	, mSocio(socio)
{

}

CLendDlg::~CLendDlg()
{
}

void CLendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CLendDlg::OnOK()
{
	CWnd *pWnd = GetDlgItem(IDC_EDIT_SOCIO);
	if (pWnd)
		pWnd->GetWindowText(mSocio.mNombre);
	pWnd = GetDlgItem(IDC_EDIT_LEND_ISBN);
	if (pWnd)
		pWnd->GetWindowText(mBook.mISBN);
	CDialogEx::OnOK();
}



BEGIN_MESSAGE_MAP(CLendDlg, CDialogEx)
END_MESSAGE_MAP()


// CLendDlg message handlers
