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


bool CBooks::Add()
{
	CBook book;
	CAddBookDlg dlg(book);
	int rc = dlg.DoModal();
	if (rc == IDOK)
	{
		return gDB.AddBook(book);
	}

	return false;

}

void CBooks::AddBooks()
{
	while (1) {
		if (!Add())
			return;
	}
}
