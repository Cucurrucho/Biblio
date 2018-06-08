#pragma once
class CHttpClient
{
public:
	CHttpClient();
	~CHttpClient();
	bool Search1(class CBook &book);
	CString GetValueFromString(const CString &s, const char *zKey);
	CString GetValueFromString2(const CString &s, const char *zKey);
	bool Search2(class CBook &book);
	
	bool MultiSearch(class CBook &book);
};

