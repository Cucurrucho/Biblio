
// BiblioDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Biblio.h"
#include "BiblioDlg.h"
#include "afxdialogex.h"
#include "CBooks.h"
#include "MyDatabase.h"
#include "Book.h"
#include "Socios.h"
#include "HttpClient.h"
#include "Lendings.h"
#include "ReturnBookDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBiblioDlg dialog



CBiblioDlg::CBiblioDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BIBLIO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBiblioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBiblioDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_EXIT, &CBiblioDlg::OnFileExit)
	ON_COMMAND(ID_BOOKS_ADD, &CBiblioDlg::OnBooksAdd)
	ON_COMMAND(ID_DATABASE_INIT, &CBiblioDlg::OnDatabaseInit)
	ON_COMMAND(ID_SOCIOS_AGREGAR, &CBiblioDlg::OnSociosAgregar)
	ON_COMMAND(ID_CLIENT_SEARCH, &CBiblioDlg::OnClientSearch)
	ON_COMMAND(ID_PRESTAR_PRESTARLIBRO, &CBiblioDlg::OnPrestarPrestarlibro)
	ON_COMMAND(ID_PRESTAR_DEVOLVER, &CBiblioDlg::OnPrestarDevolver)
END_MESSAGE_MAP()


// CBiblioDlg message handlers

BOOL CBiblioDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBiblioDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBiblioDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBiblioDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBiblioDlg::OnFileExit()
{
	exit(0);
}


void CBiblioDlg::OnBooksAdd()
{
	gBooks.Add();
}


void CBiblioDlg::OnDatabaseInit()
{
	gDB.Init();
}


void CBiblioDlg::OnSociosAgregar()
{
	gSocios.Add();
	
}



void CBiblioDlg::OnClientSearch()
{
	/*CHttpClient client;
	client.Search2();*/
}


void CBiblioDlg::OnPrestarPrestarlibro()
{
	gLendings.lend();
}


void CBiblioDlg::OnPrestarDevolver()
{
	CReturnBookDlg dlg;
	dlg.DoModal();
}
