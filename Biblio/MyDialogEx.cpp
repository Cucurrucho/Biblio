#include "stdafx.h"
#include "MyDialogEx.h"
//#include "MyWindows.h"

CMyDialogEx::CMyDialogEx(UINT nIDTemplate, CWnd* pParentWnd)
: CDialogEx(nIDTemplate, pParentWnd)
{
}

CMyDialogEx::~CMyDialogEx(void)
{
}
void CMyDialogEx::SetParameter(int id, int value)
{
    CWnd *pWnd = GetDlgItem(id);
    if (pWnd)
    {
        char zBuf[64];
        sprintf_s (zBuf, 64, "%3d", value);
        pWnd->SetWindowText(zBuf);
    }
}
void CMyDialogEx::SetParameter(int id, float value)
{
    CWnd *pWnd = GetDlgItem(id);
    if (pWnd)
    {
        char zBuf[64];
        sprintf_s (zBuf, 64, "%.3f", value);
        pWnd->SetWindowText(zBuf);
    }
}
void CMyDialogEx::SetParameter(int id, double value)
{
    CWnd *pWnd = GetDlgItem(id);
    if (pWnd)
    {
        char zBuf[64];
        sprintf_s (zBuf, 64, "%.3f", value);
        pWnd->SetWindowText(zBuf);
    }
}
void CMyDialogEx::SetParameter(int id, bool bFlag)
{
	CButton *pButton=(CButton *)GetDlgItem(id);
	if (pButton)
		pButton->SetCheck(bFlag);
}
bool CMyDialogEx::GetParameter(int id, int &oValue, int minValue, int maxValue)
{
    CWnd *pWnd = GetDlgItem(id);
    if (pWnd)
    {
        CString s;
        pWnd->GetWindowText(s);
		int n = atoi(s);
		if ( n >= minValue && n <= maxValue)
		{
			oValue = n;
			return true;
		}
    }
	return false;
}
bool CMyDialogEx::GetParameter(int id, float &oValue, float minValue, float maxValue)
{
    CWnd *pWnd = GetDlgItem(id);
    if (pWnd)
    {
        CString s;
        pWnd->GetWindowText(s);
		float n = (float)atof(s);
		if ( n >= minValue && n <= maxValue)
		{
			oValue = n;
			return true;
		}
    }
	return false;
}
bool CMyDialogEx::GetParameter(int id, double &oValue, double minValue, double maxValue)
{
    CWnd *pWnd = GetDlgItem(id);
    if (pWnd)
    {
        CString s;
        pWnd->GetWindowText(s);
		double n = atof(s);
		if ( n >= minValue && n <= maxValue)
		{
			oValue = n;
			return true;
		}
    }
	return false;
}
bool CMyDialogEx::GetParameter(int id, int &oValue)
{
    CWnd *pWnd = GetDlgItem(id);
    if (pWnd)
    {
        CString s;
        pWnd->GetWindowText(s);
		oValue = atoi(s);
		return true;
    }
	return false;
}
void CMyDialogEx::GetParameter(int id, bool &bFlag)
{
	CButton *pButton=(CButton *)GetDlgItem(id);
	if (pButton)
	{
	    int ChkState=pButton->GetCheck();
		bFlag = ChkState == BST_CHECKED;
	}
}
bool CMyDialogEx::IsChecked(int id)
{
    CButton *pButton = (CButton *)GetDlgItem(id);
	bool bChecked = (pButton->GetCheck() != 0);
    return bChecked;
}
void CMyDialogEx::SetCheck(int id, bool bCheck)
{
    CButton *pWnd=(CButton *)GetDlgItem(id);
	if (pWnd)
	{
		if (bCheck)
			pWnd->SetCheck(BST_CHECKED);
		else
			pWnd->SetCheck(BST_UNCHECKED);
	}
}
void CMyDialogEx::SetMenuCheck(int id, bool bCheck)
{
    CMenu *pMenu=GetMenu();
	if (pMenu)
	{
		if (bCheck)
			pMenu->CheckMenuItem(id, MF_BYCOMMAND | MF_CHECKED);
		else
			pMenu->CheckMenuItem(id, MF_BYCOMMAND | MF_UNCHECKED);
	}
}
void CMyDialogEx::SetTitle(const char * zText)
{
	SetWindowText(zText);
}
bool CMyDialogEx::SetText(int id, const char * zText)
{
    CWnd *pWnd = GetDlgItem(id);
    if (!pWnd)
		return false;
        
	pWnd->SetWindowText(zText);
	return true;
}
bool CMyDialogEx::SetText(int id, const char * zText1, const char * zText2)
{
	CString sText(zText1);
	sText += " ";
	sText += zText2;
	return SetText(id, sText);
}
bool CMyDialogEx::GetItemText(int id, CString &sText)
{
    CWnd *pWnd = GetDlgItem(id);
    if (!pWnd)
		return false;
        
	pWnd->GetWindowText(sText);
	static bool ubOnce = false;
	static bool ubAllowUserToInitiateCrashByText = false;
	if (!ubOnce)
	{
		ubOnce = true;
		//CMyRegistry::GetAppReg("enable_crash_by_text", ubAllowUserToInitiateCrashByText);
	}
	if (ubAllowUserToInitiateCrashByText)
	{
		if (sText.Left(7) == "crashme")
			OnUserCrash(sText);
	}
	return true;
}
CString CMyDialogEx::GetText(int id)
{
	CString s(_T("Dialog Text Not Defined"));
    CWnd *pWnd = GetDlgItem(id);
    if (pWnd)
	{      
		pWnd->GetWindowText(s);
		/*
		static bool ubOnce = false;
		static bool ubAllowUserToInitiateCrashByText = false;
		if (!ubOnce)
		{
			ubOnce = true;
			CMyRegistry::GetAppReg("enable_crash_by_text", ubAllowUserToInitiateCrashByText);
		}
		if (ubAllowUserToInitiateCrashByText)
		{
			if (sText.Left(7) == "crashme")
				OnUserCrash(sText);
		} */
	}
	return s;
}
bool CMyDialogEx::Enable(int id, bool bEnable)
{
    CWnd *pWnd = GetDlgItem(id);
    if (!pWnd)
		return false;
		
	pWnd->EnableWindow(bEnable);
	return true;
}
static int five = 5;
void CMyDialogEx::OnUserCrash(CString &sText)
{
	int four = 4;
	if (sText.Find("div") > 0)
	{
		__try
		{
			int zero = five - four - 1;
			int num = 20;
			static int kk = 0;
			kk = num / zero;
		}
		__except(GetExceptionCode() == EXCEPTION_INT_DIVIDE_BY_ZERO ? 
			EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
		{ 
			MessageBox("Exception caught","SW Test");
			/*FILE *pf = MyFOpen("d:\\MyLog\\OnCrashMe.log","w");
			if (pf)
			{
				fprintf (pf, "Crash in GLinesSet\n");
				fclose(pf);
			}*/
			throw;
		}
	}

	int *pi = 0;
	*pi = 0;
}

bool CMyDialogEx::VerifyAndGetInput(int id, int minValue, int maxValue, int & oValue, const char * zName)
{
	CString sText(_T(""));
	GetItemText(id, sText);
	if (sText.IsEmpty())
	{
		CString sErr(zName);
		sErr += " is not defined";
		MessageBox(sErr, "Missing Input");
		return false;
	}
	int inputValue = 0;
	if (!GetParameter(id, inputValue, minValue, maxValue))
	{
		char zBuf[256];
		sprintf_s(zBuf,sizeof(zBuf),"%s should be in the range %d - %d", zName, minValue, maxValue);
		MessageBox(zBuf, "Unexpected Input");
		return false;
	}
	oValue = inputValue;
	return true;
}
bool CMyDialogEx::VerifyAndGetInput(int id, float minValue, float maxValue, float & oValue, const char * zName)
{
	CString sText(_T(""));
	GetItemText(id, sText);
	if (sText.IsEmpty())
	{
		CString sErr(zName);
		sErr += " is not defined";
		MessageBox(sErr, "Missing Input");
		return false;
	}
	float inputValue = 0;
	if (!GetParameter(id, inputValue, minValue, maxValue))
	{
		char zBuf[256];
		sprintf_s(zBuf,sizeof(zBuf),"%s should be in the range %.2f - %.2f", zName, minValue, maxValue);
		MessageBox(zBuf, "Unexpected Input");
		return false;
	}
	oValue = inputValue;
	return true;
}
