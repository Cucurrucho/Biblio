// AddBookDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Biblio.h"
#include "AddBookDlg.h"
#include "afxdialogex.h"
#include "Book.h"


// CAddBookDlg dialog

IMPLEMENT_DYNAMIC(CAddBookDlg, CDialogEx)

CAddBookDlg::CAddBookDlg(CBook &book, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ADD_BOOK, pParent)
	, mBook(book)
{

}

CAddBookDlg::~CAddBookDlg()
{
}

void CAddBookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CAddBookDlg::OnOK()
{
	CWnd *pWnd = GetDlgItem(IDC_EDIT_TITULO);
	if (pWnd)
		pWnd->GetWindowText(mBook.mTitulo);
	pWnd = GetDlgItem(IDC_EDIT_AUTOR);
	if (pWnd)
		pWnd->GetWindowText(mBook.mAutor);
	pWnd = GetDlgItem(IDC_EDIT_EDITORIAL);
	if (pWnd)
		pWnd->GetWindowText(mBook.mEditorial);
	pWnd = GetDlgItem(IDC_EDIT_ISBN);
	if (pWnd)
		pWnd->GetWindowText(mBook.mISBN);
	pWnd = GetDlgItem(IDC_EDIT_GENERO);
	if (pWnd)
		pWnd->GetWindowText(mBook.mGenero);
	pWnd = GetDlgItem(IDC_EDIT_EJEMPLARES);
	if (pWnd)
	{
		CString s;
		pWnd->GetWindowText(s);
		mBook.mEjemplares = atoi(s);
	}
	pWnd = GetDlgItem(IDC_EDIT_COMENTARIO);
	if (pWnd)
		pWnd->GetWindowText(mBook.mComentario);
	CString sMissing;
	if (mBook.IsValid(sMissing))
		CDialogEx::OnOK();
	else
	{
		MessageBox("Por favor llenar el campo " + sMissing, "Faltan Campos");
	}

}

BOOL CAddBookDlg::OnInitDialog()
{
	CWnd *pWnd = GetDlgItem(IDC_EDIT_EJEMPLARES);
	if (pWnd)
		pWnd->SetWindowText("1");
	return CDialogEx::OnInitDialog();;
}



BEGIN_MESSAGE_MAP(CAddBookDlg, CDialogEx)
END_MESSAGE_MAP()


// CAddBookDlg message handlers
