#pragma once
class CMyUtil
{
public:
	CMyUtil();
	~CMyUtil();
	static void FOpenLogFile(CString &sfName, bool bAppend, bool bReportFailure);
};

