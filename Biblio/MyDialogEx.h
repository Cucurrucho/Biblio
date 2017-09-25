#pragma once
#include "afxwin.h"
#include <afxdialogex.h>

class CMyDialogEx :
	public CDialogEx
{
public:
	CMyDialogEx(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	virtual ~CMyDialogEx(void);

	void SetParameter(int id, bool bFlag);
	void SetParameter(int id, int value);
	void SetParameter(int id, float value);
	void SetParameter(int id, double value);

	bool GetParameter(int id, int &oValue);
	bool GetParameter(int id, int &oValue, int minValue, int maxValue);
	bool GetParameter(int id, float &oValue, float minValue, float maxValue);
	bool GetParameter(int id, double &oValue, double minValue, double maxValue);
	void GetParameter(int id, bool &bFlag);

	bool IsChecked(int id);
	void SetCheck(int id, bool bCheck);
	void SetMenuCheck(int id, bool bCheck);

	void SetTitle(const char * zText);
	bool SetText(int id, const char * zText);
	bool SetText(int id, const char * zText1, const char * zText2);
	bool GetItemText(int id, CString &sText);
	CString GetText(int id);
	bool Enable(int id, bool bEnable);

private:
	void OnUserCrash(CString &sText);
public:
	bool VerifyAndGetInput(int id, int minValue, int maxValue, int & oValue, const char * zName);
	bool VerifyAndGetInput(int id, float minValue, float maxValue, float & oValue, const char * zName);
};
