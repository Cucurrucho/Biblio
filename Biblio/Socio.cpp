#include "stdafx.h"
#include "Socio.h"


CSocio::CSocio()
	: mID(0)
	, mMail(_T(""))
	, mDNI(_T(""))
	, mTelefono(_T(""))
	, mDomicilio(_T(""))
	, mIngreso(_T(""))
{
	mNombre = _T("");
}


CSocio::~CSocio()
{
}


bool CSocio::IsValid()
{
	if (mNombre.IsEmpty())
		return false;
	return true;
}