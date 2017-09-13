#include "stdafx.h"
#include "Book.h"


CBook::CBook()
	: mID(0)
	, mEjemplares(0)
{
	mTitulo = _T("");
	mAutor = _T("");
	mISBN = _T("");
	mEditorial = _T("");
	mGenero = _T("");
	mComentario = _T("");
}


CBook::~CBook()
{
}


bool CBook::IsValid(CString &s)
{
	if (mTitulo.IsEmpty())
	{
		s = "Titulo";
		return false;

	}
	if (mAutor.IsEmpty())
	{
		s = "Autor";
		return false;
	}
		
	if (mEditorial.IsEmpty())
	{
		s = "Editorial";
		return false;
	}
	return true;
}
