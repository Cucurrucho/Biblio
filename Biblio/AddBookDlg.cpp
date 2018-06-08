// AddBookDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Biblio.h"
#include "AddBookDlg.h"
#include "afxdialogex.h"
#include "Book.h"
#include "HttpClient.h"


// CAddBookDlg dialog

IMPLEMENT_DYNAMIC(CAddBookDlg, CDialogEx)

CAddBookDlg::CAddBookDlg(CBook &book, CWnd* pParent /*=NULL*/)
	: CMyDialogEx(IDD_ADD_BOOK, pParent)
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
	ReadAllFields();
	CString sMissing;
	if (mBook.IsValid(sMissing))
		CDialogEx::OnOK();
	else if (!mBook.mISBN.IsEmpty())
	{
		OnBnClickedButtonBuscar();
	}
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
	ON_BN_CLICKED(IDC_BUTTON_BUSCAR, &CAddBookDlg::OnBnClickedButtonBuscar)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CAddBookDlg::OnBnClickedButtonClear)
END_MESSAGE_MAP()


// CAddBookDlg message handlers


void CAddBookDlg::OnBnClickedButtonBuscar()
{
	CWnd *pWnd = GetDlgItem(IDC_EDIT_ISBN);
	if (!pWnd)
		return;

	pWnd->GetWindowText(mBook.mISBN);
	if (mBook.mISBN.IsEmpty())
	{
		MessageBox("Por Favor llenar campo ISBN", "Aviso");
		return;
	}
	CHttpClient client;
	if (client.MultiSearch(mBook))
	{
		SetText(IDC_EDIT_TITULO, mBook.mTitulo);
		SetText(IDC_EDIT_AUTOR, mBook.mAutor);
		SetText(IDC_EDIT_EDITORIAL, mBook.mEditorial);
	}

}



void CAddBookDlg::OnBnClickedButtonClear()
{
	SetText(IDC_EDIT_TITULO, "");
	SetText(IDC_EDIT_AUTOR, "");
	SetText(IDC_EDIT_EDITORIAL, "");
	SetText(IDC_EDIT_ISBN, "");
	SetText(IDC_EDIT_GENERO, "");
	SetText(IDC_EDIT_COMENTARIO, "");
}

void CAddBookDlg::ReadAllFields(){
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
}


