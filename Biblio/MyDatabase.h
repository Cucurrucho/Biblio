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
	bool HasBook(class CBook &book);
	bool CreateSociosTable();
	bool AddSocio(class CSocio &socio);
	bool SearchBookByISBN(CBook & book);
	bool SearchBookByTitle(CBook & book);
	void DBSeeder();
	bool CreateLendingsTable();
	bool AddLending(class CBook & book, class CSocio & socio);
	bool GetSocio(class CSocio &socio);
};
extern CMyDatabase gDB;

