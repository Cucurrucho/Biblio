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


bool CHttpClient::OpenInternetConnection(CBook &book)
{
	const int N_READ = 1024;
	//CLogFile log("OpenInternetConnection");
	CInternetSession session;
	CHttpConnection* pServer = NULL;
	CHttpFile* pFile = NULL;
	FILE *pf = NULL;
	CString sServerName = "www.isbn.org.ar";
	INTERNET_PORT port = 80;
	CString sHeader = "Content-Type: application/x-www-form-urlencoded\r\n";
	CString sPath = "/web/busqueda-avanzada-resultados.php";
	//CString sParams = "ingresa=1&titulo=&isbn=9789874517630&autor=&sello=&fechad=&fechah=&enviar=Buscar";
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
			int rc = fopen_s(&pf, "d:\\MyLog\\InternetText.txt", "w");
			if (!rc)
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
					/*if (log)
					{ 
						fprintf(log.mpf, "%d: %d bytes read\n", iRead, nRead);
						for (UINT i = 0; i <= nRead; i += 16)
						{
							for (int iByte = 0; iByte < 16; iByte++)
							{
								fprintf(log.mpf, "%3u ", zBuff[i + iByte]);
								if (iByte % 8 == 7)
									fprintf(log.mpf, " - ");
							}
							for (int iChar = 0; iChar < 16; iChar++)
							{
								unsigned char ch = zBuff[i + iChar];
								if (ch == '\n')
									fprintf(log.mpf, "\\n");
								else
									fprintf(log.mpf, "%c", ch);
								//if (iChar == 7)
								//	fprintf(log.mpf, " - ");
							}
							fprintf(log.mpf, "\n");
						}
						fprintf(log.mpf, "\n");
					}*/
					nAllRead += nRead;
					fprintf(pf, "%s", zBuff);
					nRead = pFile->Read(zBuff, N_READ);
					iRead++;
					if (iRead > 100)
					{
						MessageBox(NULL,"Input text from internet too long", "Reading Book Info Failed",NULL);
						break;
					}
				}
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
				int authorNameIndex =sAuthors.Find(',');
				CString sLastName = sAuthors.Mid(0, authorNameIndex);
				CString sFirstName = sAuthors.Mid(authorNameIndex+2);
				sAuthors = sFirstName;
				sAuthors += " ";
				sAuthors += sLastName;
				book.mTitulo = sTitle;
				book.mAutor = sAuthors;
				book.mEditorial = sEditorial;
				/*if (log)
				{
					fprintf(log.mpf, "\nAll Read %d\n\n", nAllRead);
					fprintf(log.mpf, "sText:\n");
					fprintf(log.mpf, "%s\n", (const char *)sText);
					sText.Replace("&iacute;", "í");
					sText.Replace("&oacute;", "ó");
					sText.Replace("&aacute;", "á");
					sText.Replace("Ã³", "ó");
					sText.Replace("Ã±o", "ñ");
					fprintf(log.mpf, "\n\n==================> sText Corrected:\n");
					fprintf(log.mpf, "%s\n", (const char *)sText);

					CString sTitle = GetValueFromString(sText,"Título:");
					CString sAuthors = GetValueFromString(sText,"Autor/es:");

					fprintf(log.mpf, "\n\n Results:\n");
					fprintf(log.mpf, "Título: %s\n", (const char *)sTitle);
					fprintf(log.mpf, "Autor/es: %s\n", (const char *)sAuthors);
				}*/
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
CString CHttpClient::GetValueFromString(const CString &s, const char *zKey)
{
	CString sKey(zKey);
	int iKey = s.Find(zKey);
	if (iKey < 0)
		return sKey + " Not Found";
	CString sAfterKey = s.Mid(iKey + sKey.GetLength(), 200);
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
