#include "stdafx.h"
#include "CBooks.h"
#include "AddBookDlg.h"
#include "Book.h"
#include "MyDatabase.h"

CBooks gBooks;


CBooks::CBooks()
{
}


CBooks::~CBooks()
{
}


void CBooks::Add()
{
	CBook book;
	CAddBookDlg dlg(book);
	int rc = dlg.DoModal();
	if (rc == IDOK)
	{
		gDB.AddBook(book);
	}

}
