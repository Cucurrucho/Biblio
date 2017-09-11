#include "stdafx.h"
#include "MyDatabase.h"
#include "sqlite3.h"

CMyDatabase gDB;

CMyDatabase::CMyDatabase()
	: mdb(NULL)
{
}


CMyDatabase::~CMyDatabase()
{
	Close();
}


void CMyDatabase::Init()
{
	CreateBooksTable();
}


void CMyDatabase::OnError(const char* zText)
{
	char zBuff[256];
	sprintf_s(zBuff, sizeof(zBuff), "%s failed, %s", zText, sqlite3_errmsg(mdb));
	MessageBox(NULL, zBuff, "Error", NULL);
}


void CMyDatabase::Close()
{
	if (mdb) {
		int rc = sqlite3_close(mdb);
		if (rc) {
			OnError("Close Database");
		}
		else {
			mdb = NULL;
		}
	}
}


bool CMyDatabase::CreateBooksTable()
{
	if (!Open())
		return false;

	int rc;
	char *sql;
	sql = "CREATE TABLE Books ("
		"ID INTEGER PRIMARY KEY NOT NULL,"
		"Titulo			TEXT  NOT NULL,"
		"Autor          TEXT  NOT NULL,"
		"ISBN           TEXT NOT NULL,"
		"Genero         TEXT NOT NULL,"
		"Ejemplares     INTEGER DEFAULT 1,"
		"Comentario     TEXT,"
		"Timestamp DATETIME DEFAULT CURRENT_TIMESTAMP);";
	rc = sqlite3_exec(mdb, sql, NULL, NULL, NULL);
	if (rc) {
		OnError("Create Table");
	}
	else {
		MessageBox(NULL, "Table created", "Success", NULL);
	}
	Close();
	return rc == 0;
}


bool CMyDatabase::Open()
{
	if (mdb) {
		return true;
	}
	int rc = sqlite3_open("test.db", &mdb);
	if (rc) {
		OnError("Open Database");
		return false;
	}
	else {
		MessageBox(NULL, "DB opend", "Success", NULL);
		return true;
	}
}


bool CMyDatabase::AddBook(const char * zTitulo, const char * zAutor, const char * zISBN,
	const char * zGenero, const char * zComentario, int nEjemplares)
{
	if (!mdb) {
		Open();
		if (!mdb) {
			return false;
		}
	}
	CString sql;
	int rc;
	int ejemplares = HasBook(zISBN);
	if (ejemplares == 0)
	{
		char zBuff[128];
		sprintf_s(zBuff, sizeof(zBuff), "%d", nEjemplares);
		sql = "INSERT INTO BOOKS (Titulo,Autor,ISBN,Genero,Comentario,Ejemplares) ";
		sql += "Values ('";
		sql += zTitulo;
		sql += "', '";
		sql += zAutor;
		sql += "', '";
		sql += zISBN;
		sql += "', '";
		sql += zGenero;
		sql += "', '";
		sql += zComentario;
		sql += "', '";
		sql += zBuff;
		sql += "');";
		rc = sqlite3_exec(mdb, sql, NULL, NULL, NULL);
		if (rc) {
			OnError("Add Book");
			return false;
		}
		else
		{
			MessageBox(NULL, "Book Added", "Success", NULL);
		}

	}
	else
	{

	}
	
}


int CMyDatabase::HasBook(const char * zISBN)
{
	if (!Open())
		return false;

	int rc;
	CString sql;
	sql = "SELECT Ejemplares FROM Books WHERE ISBN = '";
	sql += zISBN;
	sql += "';";
	rc = sqlite3_exec(mdb, sql, NULL, NULL, NULL);
	if (rc) {
		OnError("Select error");
	}
	else {
		if (rc == NULL)
		{
			return 0;
		}
		else
		{
			return rc;
		}
	}
}
