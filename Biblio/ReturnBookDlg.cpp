// ReturnBookDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Biblio.h"
#include "ReturnBookDlg.h"
#include "afxdialogex.h"
#include "Lendings.h"
#include "Book.h"


// CReturnBookDlg dialog

IMPLEMENT_DYNAMIC(CReturnBookDlg, CMyDialogEx)

CReturnBookDlg::CReturnBookDlg(CWnd* pParent /*=NULL*/)
	: CMyDialogEx(IDD_DIALOG_RETURN_BOOK, pParent)
{

}

CReturnBookDlg::~CReturnBookDlg()
{
}

void CReturnBookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CReturnBookDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH_LENDING, &CReturnBookDlg::OnBnClickedButtonSearchLending)
END_MESSAGE_MAP()


// CReturnBookDlg message handlers


void CReturnBookDlg::OnBnClickedButtonSearchLending()
{
	CString sName(GetText(IDC_EDIT_RETURN_NOMBRE));
	if (sName.IsEmpty())
		return;
	CList<class CBook *, class CBook *> booksList;
	gLendings.GetLendedBook(sName, booksList);
}
