
// MFCApplication2Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "afxdialogex.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int divizori = 0;
int tab[10];
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


// CMFCApplication2Dlg dialog



CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MFCAPPLICATION2_DIALOG, pParent)
	, Nr(0)
	, rez(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NUMAR, Nr);
	DDX_Text(pDX, IDC_EDIT1, rez);
}

BEGIN_MESSAGE_MAP(CMFCApplication2Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_VERIFICA, &CMFCApplication2Dlg::OnBnClickedVerifica)
	ON_BN_CLICKED(IDC_RESETARE, &CMFCApplication2Dlg::OnBnClickedResetare)
	ON_BN_CLICKED(IDC_SUMA, &CMFCApplication2Dlg::OnBnClickedSuma)
	ON_BN_CLICKED(IDC_PRIM1, &CMFCApplication2Dlg::OnBnClickedPrim1)
	ON_BN_CLICKED(IDC_PRIM2, &CMFCApplication2Dlg::OnBnClickedPrim2)
END_MESSAGE_MAP()


// CMFCApplication2Dlg message handlers

BOOL CMFCApplication2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

void CMFCApplication2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication2Dlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int prim(int n) {
	int d = 2;
	while (d * d <= n && n % d != 0)
		d++;
	divizori = d;
	return d * d > n&& n > 1;
}

void CMFCApplication2Dlg::OnBnClickedVerifica()
{
	UpdateData();
	int n = Nr;
	if (!prim(n))
	{
		rez.Format((LPCWSTR)L"Numarul %d nu este prim (se divide prin %d)", n, divizori);
	}
	else {
		rez.Format((LPCWSTR)L"Numarul %d este prim", n);
	}
	UpdateData(FALSE);
}

void CMFCApplication2Dlg::OnBnClickedResetare()
{
	Nr = 0;
	rez = "";
	UpdateData(FALSE);
}

CString divi(int n) {
	int s = 0;
	CString text;
	for (int i = 2; i <= n / 2; i++)
		if (n % i == 0) {
			s = s + i;
			tab[i] = i;
			text.AppendFormat(L"%d+" , tab[i]);
		}
	text.Delete(text.GetLength() - 1);
	return text;

}
void CMFCApplication2Dlg::OnBnClickedSuma()
{
	UpdateData();
	int n = Nr, s=0;
	for (int i = 2; i <= n / 2; i++)
		if (n % i == 0) {
			s = s + i;
			tab[i] = s;
		}
	rez.Format((LPCWSTR)L"Suma divizorilor proprii ai nr %d este %d=%s", n, s, divi(n));
	UpdateData(FALSE);
}

void CMFCApplication2Dlg::OnBnClickedPrim1()
{
	UpdateData();
	int n = Nr;
	if (n == 0)
		return;
	while (true) {
		n++;
		if (prim(n)) {
			break;
		}
	}
	rez.Format((LPCWSTR)L"Cel mai mare numar prim dupa %d este %d", Nr, n);
	UpdateData(FALSE);
}

void CMFCApplication2Dlg::OnBnClickedPrim2()
{
	UpdateData();
	int n = Nr;
	if (n == 0)
		return;
	if (n > 2) {
		while (true) {
			n--;
			if (prim(n)) {
				break;
			}
		}
	}
	rez.Format((LPCWSTR)L"Cel mai mic numar prim dupa %d este %d", Nr, n);
	UpdateData(FALSE);
}
