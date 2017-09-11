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
	bool AddBook(const char * zTitulo, const char * zAutor, const char * zISBN,
		const char * zGenero, const char * zComentario = NULL, int nEjemplares = 1);
	int HasBook(const char * zISBN);
};
extern CMyDatabase gDB;

