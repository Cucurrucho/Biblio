#pragma once
class CBook
{
public:
	CBook();
	~CBook();
	int mID;
	CString mTitulo;
	CString mAutor;
	CString mISBN;
	CString mEditorial;
	CString mGenero;
	CString mComentario;
	int mEjemplares;
	bool IsValid(CString &s);
};

