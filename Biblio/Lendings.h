#pragma once
class CLendings
{
public:
	CLendings();
	~CLendings();
	void lend();
	int GetLendedBook(const char * zUser, CList<class CBook *, class CBook *> &booksList);
};
extern CLendings gLendings;

