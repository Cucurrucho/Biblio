#pragma once
class CHttpClient
{
public:
	CHttpClient();
	~CHttpClient();
	bool OpenInternetConnection(class CBook &book);
	CString GetValueFromString(const CString &s, const char *zKey);
	bool Search2();
};

