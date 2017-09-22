#pragma once
class CMyDatabase
{
public:
	CMyDatabase();
	~CMyDatabase();
	void Init();
private:
	struct sqlite3 *mdb;
public:
	void OnError(const char* zText);
	void Close();
	bool CreateBooksTable();
	bool Open();
	bool AddBook(class CBook &book);
	int HasBook(class CBook &book);
	bool CreateSociosTable();
	bool AddSocio(class CSocio &socio);
};
extern CMyDatabase gDB;

