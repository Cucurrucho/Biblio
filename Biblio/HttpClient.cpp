#include "stdafx.h"
#include "HttpClient.h"
#include "afxinet.h"
#include "Book.h"


CHttpClient::CHttpClient()
{
}


CHttpClient::~CHttpClient()
{
}


bool CHttpClient::Search1(CBook &book)
{
	const int N_READ = 1024;
	CInternetSession session;
	CHttpConnection* pServer = NULL;
	CHttpFile* pFile = NULL;
	FILE *pf = NULL;
	CString sServerName = "www.isbn.org.ar";
	INTERNET_PORT port = 80;
	CString sHeader = "Content-Type: application/x-www-form-urlencoded\r\n";
	CString sPath = "/web/busqueda-avanzada-resultados.php";
	CString sParams = "ingresa=1&titulo=&isbn=";
	sParams += book.mISBN;
	sParams += "&autor=&sello=&fechad=&fechah=&enviar=Buscar";
	try
	{
		DWORD dwRet = 0;
		pServer = session.GetHttpConnection(sServerName, port);
		pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_POST, sPath);
		pFile->AddRequestHeaders(sHeader);
		pFile->SendRequest(NULL, 0, (LPVOID)(LPCTSTR)sParams, sParams.GetLength());
		pFile->QueryInfoStatusCode(dwRet);
		CString sText;


		if (dwRet == HTTP_STATUS_OK)
		{
			fopen_s(&pf, "c:\\MyLog\\InternetText.txt", "w");
			{
				unsigned char zBuff[N_READ+1];
				int nAllRead = 0;
				UINT nRead = pFile->Read(zBuff, N_READ);
				int iRead = 0;
				while (nRead > 0)
				{
					for (int iFill = nRead; iFill <= N_READ; iFill++)
						zBuff[iFill] = 0;
					sText += (const char *)zBuff;
					nAllRead += nRead;
					if (pf)
						fprintf(pf, "%s", zBuff);
					nRead = pFile->Read(zBuff, N_READ);
					iRead++;
					if (iRead > 100)
					{
						MessageBox(NULL,"Input text from internet too long", "Reading Book Info Failed",NULL);
						break;
					}
				}
				if (pf)
					fclose(pf);
				sText.Replace("&iacute;", "í");
				sText.Replace("&oacute;", "ó");
				sText.Replace("&aacute;", "á");
				sText.Replace("Ã³", "ó");
				sText.Replace("Ã±o", "ñ");
				sText.Replace("Ã­", "í");
				sText.Replace("Ã¡", "á");
				sText.Replace("Ã©", "é");
				sText.Replace("Ã³", "ó");
				CString sTitle = GetValueFromString(sText, "Título:");
				CString sAuthors = GetValueFromString(sText, "Autor/es:");
				CString sEditorial = GetValueFromString(sText, "Sello Editor:");
				/*int authorNameIndex =sAuthors.Find(',');
				CString sLastName = sAuthors.Mid(0, authorNameIndex);
				CString sFirstName = sAuthors.Mid(authorNameIndex+2);
				sAuthors = sFirstName;
				sAuthors += " ";
				sAuthors += sLastName;*/
				book.mTitulo = sTitle;
				book.mAutor = sAuthors;
				book.mEditorial = sEditorial;
				
			}
		
		}
		delete pFile;
		delete pServer;
		session.Close();
		return true;

	}
	catch (CInternetException* pEx)
	{
		//catch errors from WinInet
		TCHAR zError[64];
		pEx->GetErrorMessage(zError, 64);
		_tprintf_s(_T("%63s"), zError);
	}

	return false;
}
CString CHttpClient::GetValueFromString(const CString &s, const char *zKey)
{
	CString sKey(zKey);
	int iKey = s.Find(zKey);
	if (iKey < 0)
		return CString();
	CString sAfterKey = s.Mid(iKey + sKey.GetLength(), 200);
	sAfterKey.TrimLeft(' ');
	sAfterKey.TrimLeft('>');
	sAfterKey.TrimLeft(' ');
	while (!sAfterKey.IsEmpty())
	{
		if (sAfterKey[0] == '<')
		{
			int iLast = sAfterKey.Find('>');
			if (iLast > 0)
			{
				sAfterKey = sAfterKey.Right(sAfterKey.GetLength() - iLast - 1);
				sAfterKey.TrimLeft(' ');
			}
		}
		else
			break;
	}
	int iAfter = sAfterKey.Find('<');
	CString sRes = sAfterKey.Left(iAfter);
	sRes.TrimRight(';');
	return sRes;
}
CString CHttpClient::GetValueFromString2(const CString &s, const char *zKey)
{
	CString sKey('\"');
	sKey += zKey;
	sKey += '\"';
	int iKey = s.Find(sKey);
	if (iKey < 0)
		return sKey + " No Encontrado";
	CString sAfterKey = s.Mid(iKey + sKey.GetLength(), 300);
	int iOpen = sAfterKey.Find('<');
	int iClose = sAfterKey.Find('>');
	if (iClose >= 0 && iClose + 1 < iOpen)
	{ 
		int len = iOpen - iClose - 1;
		sAfterKey = sAfterKey.Mid(iClose + 1, len);
	}
	sAfterKey.TrimLeft(' ');
	while (!sAfterKey.IsEmpty())
	{
		if (sAfterKey[0] == '<')
		{
			int iLast = sAfterKey.Find('>');
			if (iLast > 0)
			{
				sAfterKey = sAfterKey.Right(sAfterKey.GetLength() - iLast - 1);
				sAfterKey.TrimLeft(' ');
			}
		}
		else
			break;
	}
	int iAfter = sAfterKey.Find('<');
	CString sRes = (iAfter > 0) ? sAfterKey.Left(iAfter) : sAfterKey;
	sRes.TrimRight(';');
	return sRes;
}


bool CHttpClient::Search2(CBook &book)
{
	const int N_READ = 1024;
	CInternetSession session;
	CHttpConnection* pServer = NULL;
	CHttpFile* pFile = NULL;
	FILE *pf = NULL;
	FILE *pfLog = NULL;
	CString sServerName = "www.bookfinder.com";
	INTERNET_PORT port = 80;
	CString sPath = "/search/?author=&title=&lang=any&isbn=";
	sPath += book.mISBN;
	sPath += "&new_used=*&destination=us&currency=USD&mode=basic&st=sr&ac=qr";
	try
	{
		DWORD dwRet = 0;
		pServer = session.GetHttpConnection(sServerName, port);
		pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET, sPath);
		pFile->SendRequest();
		pFile->QueryInfoStatusCode(dwRet);
		CString sText;

		if (dwRet == HTTP_STATUS_OK)
		{
			int rc = fopen_s(&pf, "d:\\MyLog\\NewInterntText.txt", "w");
			rc = fopen_s(&pfLog, "d:\\MyLog\\NewInterntText_Log.txt", "w");
			if (!rc)
			{
				unsigned char zBuff[N_READ + 1];
				int nAllRead = 0;
				UINT nRead = pFile->Read(zBuff, N_READ);
				int iRead = 0;
				while (nRead > 0)
				{
					for (int iFill = nRead; iFill <= N_READ; iFill++)
						zBuff[iFill] = 0;
					sText += (const char *)zBuff;
					if (pfLog)
					{
						fprintf(pfLog, "%d: %d bytes read\n", iRead, nRead);
						for (UINT i = 0; i <= nRead; i += 16)
						{
							for (int iByte = 0; iByte < 16; iByte++)
							{
								fprintf(pfLog, "%3u ", zBuff[i + iByte]);
								if (iByte % 8 == 7)
								fprintf(pfLog, " - ");
							}
							for (int iChar = 0; iChar < 16; iChar++)
							{
								unsigned char ch = zBuff[i + iChar];
								if (ch == '\n')
									fprintf(pfLog, "\\n");
								else
									fprintf(pfLog, "%c", ch);
							}
							fprintf(pfLog, "\n");
						}
						fprintf(pfLog, "\n");
					}
					nAllRead += nRead;
					if (pf)
						fprintf(pf, "%s", zBuff);
					nRead = pFile->Read(zBuff, N_READ);
					iRead++;
					if (iRead > 1000)
					{
						MessageBox(NULL, "Input text from internet too long", "Reading Book Info Failed", NULL);
						break;
					}
				}
				if (pf)
					fclose(pf);
				sText.Replace("&iacute;", "í");
				sText.Replace("&oacute;", "ó");
				sText.Replace("&aacute;", "á");
				sText.Replace("Ã³", "ó");
				sText.Replace("Ã±o", "ñ");
				sText.Replace("Ã­", "í");
				sText.Replace("Ã¡", "á");
				sText.Replace("Ã©", "é");
				sText.Replace("Ã³", "ó");
				CString sTitle = GetValueFromString2(sText, "name");
				CString sAuthors = GetValueFromString2(sText, "author");
				CString sEditorial = GetValueFromString2(sText, "publisher");
				int authorNameIndex =sAuthors.Find(',');
				if (authorNameIndex > 0)
				{
					CString sLastName = sAuthors.Mid(0, authorNameIndex);
					CString sFirstName = sAuthors.Mid(authorNameIndex+2);
					sAuthors = sFirstName;
					sAuthors += " ";
					sAuthors += sLastName;
				}
				book.mTitulo = sTitle;
				book.mAutor = sAuthors;
				book.mEditorial = sEditorial;
				if (pfLog)
				{
					fprintf(pfLog, "\nAll Read %d\n\n", nAllRead);
					fprintf(pfLog, "sText:\n");
					fprintf(pfLog, "%s\n", (const char *)sText);
					sText.Replace("&iacute;", "í");
					sText.Replace("&oacute;", "ó");
					sText.Replace("&aacute;", "á");
					sText.Replace("Ã³", "ó");
					sText.Replace("Ã±o", "ñ");
					fprintf(pfLog, "\n\n==================> sText Corrected:\n");
					fprintf(pfLog, "%s\n", (const char *)sText);

					//sTitle = GetValueFromString(sText,"Título:");
					//sAuthors = GetValueFromString(sText,"Autor/es:");

					fprintf(pfLog, "\n\n Results:\n");
					fprintf(pfLog, "Título: %s\n", (const char *)sTitle);
					fprintf(pfLog, "Autor/es: %s\n", (const char *)sAuthors);
					fprintf(pfLog, "Editorial: %s\n", (const char *)sEditorial);
				}
			}
			else
			{
				MessageBox(NULL, "failed to open file, OpenInternetConnection", "error", NULL);
			}

		}
		delete pFile;
		delete pServer;
		session.Close();
		return true;

	}
	catch (CInternetException* pEx)
	{
		//catch errors from WinInet
		TCHAR zError[64];
		pEx->GetErrorMessage(zError, 64);
		_tprintf_s(_T("%63s"), zError);
	}

	return false;
}


bool CHttpClient::MultiSearch( CBook &book)
{
	Search1(book);
	if (!book.mTitulo.IsEmpty() && !book.mAutor.IsEmpty())
		return true;
	Search2(book);
	if (!book.mTitulo.IsEmpty() && !book.mAutor.IsEmpty())
		return true;
	return false;
}
