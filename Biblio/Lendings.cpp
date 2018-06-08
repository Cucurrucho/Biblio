#include "stdafx.h"
#include "Lendings.h"
#include "Book.h"
#include "Socio.h"
#include "LendDlg.h"
#include "MyDatabase.h"
#include "Lend.h"

CLendings gLendings;

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
	{
		CLend cLend(book,socio);
		gDB.AddLending(cLend);
	}
}


int CLendings::GetLendedBook(const char * zUser, CList<class CBook *, class CBook *> &booksList)
{
	CSocio socio;
	socio.mNombre = zUser;
	if (!gDB.GetSocio(socio))
	{
		MessageBox(NULL, "El socio no esta en el base de datos", "Error", NULL);
		return 0;
	}

}
