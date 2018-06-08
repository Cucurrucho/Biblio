#include "stdafx.h"
#include "MyDatabase.h"
#include "sqlite3.h"
#include "Book.h"
#include "Socio.h"
#include "Lend.h"

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
	CreateSociosTable();
	CreateLendingsTable();
	//DBSeeder();
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
		"Editorial          TEXT  NOT NULL,"
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
	if (!HasBook(book))
	{
		char zBuff[128];
		sprintf_s(zBuff, sizeof(zBuff), "%d", book.mEjemplares);
		sql = "INSERT INTO BOOKS (Titulo,Autor,Editorial,ISBN,Genero,Comentario,Ejemplares) ";
		sql += "Values ('";
		sql += book.mTitulo;
		sql += "', '";
		sql += book.mAutor;
		sql += "', '";
		sql += book.mEditorial;
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
		MessageBox(NULL, "El libro ya esta en el bas de datos", "Aviso", NULL);
		return true;
		/*int result = MessageBox(NULL, "El libro ya esta fichado, desea agregar ejemplar", "Libro Fichado", MB_YESNO);
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
		}*/
	}
	
}


bool CMyDatabase::HasBook(CBook &book)
{
	if (!book.mISBN.IsEmpty()) {
		if (SearchBookByISBN(book))
			return true;
	}
	if (!book.mTitulo.IsEmpty())
		return SearchBookByTitle(book);
	return false;
}


bool CMyDatabase::CreateSociosTable()
{
	if (!Open())
		return false;

	int rc;
	char *sql;
	sql = "CREATE TABLE Socios ("
		"ID INTEGER PRIMARY KEY NOT NULL,"
		"Nombre			TEXT  NOT NULL,"
		"DNI			TEXT,"
		"Telefono		TEXT,"
		"Mail			TEXT,"
		"Domicilio		TEXT,"
		"Ingreso		DATETIME,"
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


bool CMyDatabase::AddSocio(CSocio &socio)
{
	if (!mdb) {
		Open();
		if (!mdb) {
			return false;
		}
	}
	CString sql;
	int rc;
	sql = "INSERT INTO Socios (Nombre,DNI,Telefono,Mail,Domicilio,Ingreso) VALUES ('";
	sql += socio.mNombre;
	sql += "', '";
	sql += socio.mDNI;
	sql += "', '";
	sql += socio.mTelefono;
	sql += "', '";
	sql += socio.mMail;
	sql += "', '";
	sql += socio.mDomicilio;
	sql += "', '";
	sql += socio.mIngreso;
	sql += "');";
	rc = sqlite3_exec(mdb, sql, NULL, NULL, NULL);
	if (rc != SQLITE_OK) {
		OnError("Agregar Socio");
		return false;
	}
	else
	{
		MessageBox(NULL, "Socio Agregado", "Exito", NULL);
		return true;
	}
}

bool CMyDatabase::SearchBookByISBN(CBook & book)
{
	if (!Open())
		return false;

	sqlite3_stmt *stmt;
	CString sql = "SELECT * FROM Books WHERE ISBN = '";
	sql += book.mISBN;
	sql += "';";
	int rc = sqlite3_prepare_v2(mdb, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		OnError("Statment error");
		return false;
	}
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_ROW && rc != SQLITE_DONE)
	{
		OnError("Select Error");
		sqlite3_finalize(stmt);
		return false;
	}
	if (rc == SQLITE_DONE)
	{
			sqlite3_finalize(stmt);
			return false;
	}
	book.mID = sqlite3_column_int(stmt, 0);
	book.mTitulo = sqlite3_column_text(stmt, 1);
	book.mAutor = sqlite3_column_text(stmt, 2);
	book.mEditorial = sqlite3_column_text(stmt, 3);
	book.mGenero = sqlite3_column_text(stmt, 5);
	book.mEjemplares = sqlite3_column_int(stmt, 6);
	book.mComentario = sqlite3_column_text(stmt, 7);
	sqlite3_finalize(stmt);
	return true;
}


bool CMyDatabase::SearchBookByTitle(CBook & book)
{
	if (!Open())
		return false;

	sqlite3_stmt *stmt;
	CString sql = "SELECT * FROM Books WHERE ISBN = '";
	sql += book.mISBN;
	sql += "';";
	int rc = sqlite3_prepare_v2(mdb, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		OnError("Statment error");
		return false;
	}
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_ROW && rc != SQLITE_DONE)
	{
		OnError("Select Error");
		sqlite3_finalize(stmt);
		return false;
	}
	if (rc == SQLITE_DONE)
	{
		sqlite3_finalize(stmt);
		return false;
	}
	book.mID = sqlite3_column_int(stmt, 0);
	book.mAutor = sqlite3_column_text(stmt, 2);
	book.mEditorial = sqlite3_column_text(stmt, 3);
	book.mISBN = sqlite3_column_text(stmt, 4);
	book.mGenero = sqlite3_column_text(stmt, 5);
	book.mEjemplares = sqlite3_column_int(stmt, 6);
	book.mComentario = sqlite3_column_text(stmt, 7);
	sqlite3_finalize(stmt);
	return true;
}


void CMyDatabase::DBSeeder()
{
	CBook book;
	book.mAutor = "Bla Autor";
	book.mEditorial = "Bla Editorial";
	book.mTitulo = "Bla1 Title";
	book.mEjemplares = 1;
	book.mGenero = "Historia";
	book.mISBN = "123456";
	AddBook(book);
	book.mISBN = "0000";
	book.mTitulo = "Bla2 Title";
	AddBook(book);
	CSocio socio;
	socio.mNombre = "Adam Bar";
	AddSocio(socio);
	socio.mNombre = "Nur";
	AddSocio(socio);
}


bool CMyDatabase::CreateLendingsTable()
{
	if (!Open())
		return false;

	int rc;
	char *sql;
	sql = "CREATE TABLE Lendings ("
		"Socio_ID	INTEGER NOT NULL,"
		"Book_ID	INTEGER	NOT	NULL,"
		"Timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,"
		"CONSTRAINT id PRIMARY KEY (Socio_ID, Book_ID)"
		");";
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


bool CMyDatabase::AddLending(CLend &lend)
{
	CBook book = lend.mBook;
	CSocio socio = lend.mSocio;
	if (!HasBook(book))
	{
		MessageBox(NULL, "El libro no esta en el base de datos", "Aviso", NULL);
		return false;
	}
	if (!GetSocio(socio))
	{
		MessageBox(NULL, "El Usuario no esta en el base de datos", "Aviso", NULL);
		return false;
	}
	if (!mdb) {
		Open();
		if (!mdb) {
			return false;
		}
	}
	CString sql;
	char socio_id[33];
	char book_id[33];
	_itoa_s(socio.mID, socio_id, 10);
	_itoa_s(book.mID, book_id, 10);
	int rc;
	sql = "INSERT INTO Lendings (Socio_ID,Book_ID) VALUES ('";
	sql += socio_id;
	sql += "', '";
	sql += book_id;
	sql += "');";
	rc = sqlite3_exec(mdb, sql, NULL, NULL, NULL);
	if (rc != SQLITE_OK) {
		OnError("Prestamo");
		return false;
	}
	else
	{
		MessageBox(NULL, "Libro Prestado", "Exito", NULL);
		return true;
	}
	
}


bool CMyDatabase::GetSocio(CSocio &socio)
{
	if (!Open())
		return false;

	sqlite3_stmt *stmt;
	CString sql = "SELECT * FROM Socios WHERE Nombre = '";
	sql += socio.mNombre;
	sql += "'";
	int rc = sqlite3_prepare_v2(mdb, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		OnError("Statment error");
		return false;
	}
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_ROW && rc != SQLITE_DONE)
	{
		OnError("Select Error");
		sqlite3_finalize(stmt);
		return false;
	}
	if (rc == SQLITE_DONE)
	{
		sqlite3_finalize(stmt);
		return false;
	}
	socio.mID = sqlite3_column_int(stmt, 0);
	sqlite3_finalize(stmt);
	return true;
}
