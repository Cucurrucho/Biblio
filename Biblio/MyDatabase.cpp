#include "stdafx.h"
#include "MyDatabase.h"
#include "sqlite3.h"
#include "Book.h"

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
		"ISBN           TEXT,"
		"Genero         TEXT,"
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
	if (rc != SQLITE_OK) {
		OnError("Open Database");
		return false;
	}
	else {
		return true;
	}
}


bool CMyDatabase::AddBook(CBook &book)
{
	if (!mdb) {
		Open();
		if (!mdb) {
			return false;
		}
	}
	CString sql;
	int rc;
	int ejemplares = HasBook(book);
	if (ejemplares == -1)
	{
		MessageBox(NULL, "Error de lectura de BD", "Error", NULL);
		return false;
	}
	if (ejemplares == 0)
	{
		char zBuff[128];
		sprintf_s(zBuff, sizeof(zBuff), "%d", book.mEjemplares);
		sql = "INSERT INTO BOOKS (Titulo,Autor,ISBN,Genero,Comentario,Ejemplares) ";
		sql += "Values ('";
		sql += book.mTitulo;
		sql += "', '";
		sql += book.mAutor;
		sql += "', '";
		sql += book.mISBN;
		sql += "', '";
		sql += book.mGenero;
		sql += "', '";
		sql += book.mComentario;
		sql += "', '";
		sql += zBuff;
		sql += "');";
		rc = sqlite3_exec(mdb, sql, NULL, NULL, NULL);
		if (rc != SQLITE_OK) {
			OnError("Add Book");
			return false;
		}
		else
		{
			MessageBox(NULL, "Libro Fichado", "Exito", NULL);
			return true;
		}

	}
	else
	{
		int result = MessageBox(NULL, "El libro ya esta fichado, desea agregar ejemplar", "Libro Fichado", MB_YESNO);
		if (result == IDYES) {
			char zBuff[128];
			sprintf_s(zBuff, sizeof(zBuff), "%d", book.mEjemplares + ejemplares);
			sql = "UPDATE Books SET Ejemplares = ";
			sql += zBuff;
			sql += " WHERE ISBN = '";
			sql += book.mISBN;
			sql += "';";
			rc = sqlite3_exec(mdb, sql, NULL, NULL, NULL);
			if (rc != SQLITE_OK)
			{
				OnError("Update Error");
				return false;
			}
			else
			{
				MessageBox(NULL, "Libro Actualizado", "Exito", NULL);
				return true;
			}
		}
		else
		{
			return true;
		}
	}
	
}


int CMyDatabase::HasBook(CBook &book)
{
	if (!Open())
		return false;

	sqlite3_stmt *stmt;
	CString sql = "SELECT Ejemplares FROM Books WHERE ISBN = '";
	sql += book.mISBN;
	sql += "';";
	int rc = sqlite3_prepare_v2(mdb, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		OnError("Statment error");
		return -1;
	}
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_ROW && rc != SQLITE_DONE)
	{
		OnError("Select Error");
		sqlite3_finalize(stmt);
		return -1;
	}
	if (rc == SQLITE_DONE)
	{
		sqlite3_finalize(stmt);
		sql = "SELECT Ejemplares FROM Books WHERE Titulo = '";
		sql += book.mTitulo;
		sql += "';";
		rc = sqlite3_prepare_v2(mdb, sql, -1, &stmt, NULL);
		if (rc != SQLITE_OK)
		{
			OnError("Statment error");
			return -1;
		}
		rc = sqlite3_step(stmt);
		if (rc != SQLITE_ROW && rc != SQLITE_DONE)
		{
			OnError("Select Error");
			sqlite3_finalize(stmt);
			return -1;
		}
		if (rc == SQLITE_DONE)
		{
			sqlite3_finalize(stmt);
			return 0;
		}
		int ejemplares = sqlite3_column_int(stmt, 0);
		sqlite3_finalize(stmt);
		return ejemplares;
	}
	int ejemplares = sqlite3_column_int(stmt,0);
	sqlite3_finalize(stmt);
	return ejemplares;
	
}
