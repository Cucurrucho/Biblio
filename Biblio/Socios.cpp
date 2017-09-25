#include "stdafx.h"
#include "Socios.h"
#include "Socio.h"
#include "AddSocioDlg.h"
#include "MyDatabase.h"

CSocios gSocios;

CSocios::CSocios()
{
}


CSocios::~CSocios()
{
}


void CSocios::Add()
{
	CSocio socio;
	CAddSocioDlg dlg(socio);
	int rc = dlg.DoModal();
	if (rc == IDOK)
	{
		gDB.AddSocio(socio);
	}
}
