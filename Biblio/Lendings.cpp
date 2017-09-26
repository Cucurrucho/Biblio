#include "stdafx.h"
#include "Lendings.h"
#include "Book.h"
#include "Socio.h"
#include "LendDlg.h"
#include "MyDatabase.h"


CLendings::CLendings()
{
}


CLendings::~CLendings()
{
}


void CLendings::lend()
{
	CBook book;
	CSocio socio;
	CLendDlg dlg(book, socio);
	int rc = dlg.DoModal();
	if (rc == IDOK)
		gDB.AddLending(book, socio);
}
