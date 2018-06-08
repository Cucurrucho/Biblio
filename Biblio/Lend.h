#pragma once
class CLend
{
public:
	CLend(const class CBook &book,const class CSocio &socio);
	~CLend();
	const class CBook &mBook;
	const class CSocio &mSocio;
};

