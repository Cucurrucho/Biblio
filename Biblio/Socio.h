#pragma once
#include "afxdtctl.h"
class CSocio
{
public:
	CSocio();
	~CSocio();
	CString mNombre;
	int mID;
	bool IsValid();
	CString mMail;
	CString mDNI;
	CString mTelefono;
	CString mIngreso;
	CString mDomicilio;
};

