// LendBookDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Biblio.h"
#include "LendBookDlg.h"
#include "afxdialogex.h"


// CLendBookDlg dialog

IMPLEMENT_DYNAMIC(CLendBookDlg, CDialogEx)

CLendBookDlg::CLendBookDlg(CBook &book, CSocio &socio, CWnd* pParent /*=NULL*/)
	: CMyDialogEx(IDD_LEND_BOOK, pParent)
	, mBook(book)
	, mSocio(socio)
{

}

CLendBookDlg::~CLendBookDlg()
{
}

void CLendBookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
void OnOK() {
}

BEGIN_MESSAGE_MAP(CLendBookDlg, CDialogEx)
END_MESSAGE_MAP()


// CLendBookDlg message handlers
