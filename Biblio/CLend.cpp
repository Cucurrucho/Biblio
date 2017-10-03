#include "stdafx.h"
#include "Lend.h"
#include "Book.h"
#include "Socio.h"


CLend::CLend(const CBook &book, const CSocio &socio)
	: mBook(book)
	, mSocio(socio)
{
}


CLend::~CLend()
{
}
