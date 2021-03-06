
// USBControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "USBControl.h"
#include "USBControlDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()

private:
	CFont   m_clsFont;
	CString m_Text1;
	CString m_Msg;

	bool ShowImageFromIDResource(UINT nID, LPCTSTR lpType,
						  int iWidth, int iHight, int iOffsetX = 0,int iOffsetY = 0); 

public:
	afx_msg void OnPaint();
};


CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//m_clsFont.CreatePointFont(120,_T("Arial"));
	m_clsFont.CreateFont(18, 0, 0, 0, FW_HEAVY,
                         FALSE, FALSE, FALSE, 0, 
						 OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, 
						 _T("Arial")); 

	m_Text1 = cstrToolName + '\n' + cstrToolVer + '\n' + cstrCopyRight;
}



bool  CAboutDlg::ShowImageFromIDResource(UINT nID, LPCTSTR lpType,
							  int iWidth, int iHight, int iOffsetX,int iOffsetY)  
{  
	HINSTANCE hInst = AfxGetResourceHandle();  
	HRSRC hRsrc = ::FindResource (hInst,MAKEINTRESOURCE(nID),lpType);   
	if(hRsrc == NULL) 	return false; 

	DWORD dwLen = SizeofResource(hInst, hRsrc);  
	BYTE* lpRsrc = (BYTE*)LoadResource(hInst, hRsrc);  
	if (!lpRsrc)	    return false;


	HGLOBAL m_hMem = GlobalAlloc(GMEM_FIXED, dwLen);  
	BYTE* pmem = (BYTE*)GlobalLock(m_hMem);  
	memcpy(pmem,lpRsrc,dwLen);  
	IStream* pstm;  
	CreateStreamOnHGlobal(m_hMem,FALSE,&pstm);    

	CDC      *pDC = GetDC();
	Graphics  graphics( pDC->m_hDC);
	Image     dlgImage(pstm);
	graphics.DrawImage(&dlgImage,iOffsetX,iOffsetY,iWidth,iHight);

	GlobalUnlock(m_hMem);  
	pstm->Release();  
	FreeResource(lpRsrc); 

	return true;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()



void CAboutDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages

	//Show Logo
	ShowImageFromIDResource(IDB_PNG1, _T("PNG"),130,100,130,100);
	//ShowImageFromIDResource(IDR_GIF1, _T("GIF"),350,80,60,100);

	//Show Text
	GetDlgItem(IDC_STATIC_ABOUT_1)->SetWindowText(m_Text1);
	GetDlgItem(IDC_STATIC_ABOUT_1)->SetFont(&m_clsFont);
		m_Msg.LoadString(STR_INFOR_TEXT_ABOUT);
	GetDlgItem(IDC_STATIC_ABOUT_3)->SetWindowText(m_Msg);
}


// CUSBControlDlg dialog

CUSBControlDlg::CUSBControlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUSBControlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUSBControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TAB1, m_tabPage);
}

BEGIN_MESSAGE_MAP(CUSBControlDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1_BOWSER, &CUSBControlDlg::OnBnClickedButton1Bowser)
END_MESSAGE_MAP()


// CUSBControlDlg message handlers

BOOL CUSBControlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	Init();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUSBControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUSBControlDlg::OnPaint()
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

		//Show Logo
		ShowImageFromIDResource(IDB_PNG1, _T("PNG"),120,80,500,5);
	}
}

bool  CUSBControlDlg::ShowImageFromIDResource(UINT nID, LPCTSTR lpType,
								  int iWidth, int iHight, int iOffsetX,int iOffsetY)  
{  

	HINSTANCE hInst = AfxGetResourceHandle();  
	HRSRC hRsrc = ::FindResource (hInst,MAKEINTRESOURCE(nID),lpType);   
	if(hRsrc == NULL) 	return false; 

	DWORD dwLen = SizeofResource(hInst, hRsrc);  
	BYTE* lpRsrc = (BYTE*)LoadResource(hInst, hRsrc);  
	if (!lpRsrc)	    return false;


	HGLOBAL m_hMem = GlobalAlloc(GMEM_FIXED, dwLen);  
	BYTE* pmem = (BYTE*)GlobalLock(m_hMem);  
	memcpy(pmem,lpRsrc,dwLen);  
	IStream* pstm;  
	CreateStreamOnHGlobal(m_hMem,FALSE,&pstm);    

	CDC      *pDC = GetDC();
	Graphics  graphics( pDC->m_hDC);
	Image     dlgImage(pstm);
	graphics.DrawImage(&dlgImage,iOffsetX,iOffsetY,iWidth,iHight);

	GlobalUnlock(m_hMem);  
	pstm->Release();  
	FreeResource(lpRsrc); 

	return true;
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUSBControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CUSBControlDlg::~CUSBControlDlg()
{
	GdiplusShutdown( (ULONG_PTR)m_pGdiToken);
	CoUninitialize();
}

void CUSBControlDlg::Init()
{	
	//Init Com to avoid file dialog crash.
	CoInitialize(NULL);

	//Init GDI+
	GdiplusStartup((ULONG_PTR *)&m_pGdiToken,&m_gdiplusStartupInput,NULL);

	//Set main dialog title
	this->SetWindowText( cstrToolName );

	
	//Logo Caption Static Text	
	//m_clsFontLogoCaption.CreatePointFoznt(180,_T("Arial"));
	m_clsFontLogoCaption.CreateFont( 26, 0, 0, 0, FW_HEAVY,
									 FALSE, FALSE, FALSE, 0, 
									 OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, 
									 _T("Arial") ); 

	GetDlgItem(IDC_STATIC_LOGO_CAPTION)->SetFont(&m_clsFontLogoCaption);
	GetDlgItem(IDC_STATIC_LOGO_CAPTION)->SetWindowText( cstrToolName ) ;


	//Page
	m_tabPage.InsertItem(PAGE_BASIC, _T("Basic") );
	//m_tabPage.InsertItem(PAGE_ADVANCE, _T("Advance") );//modified by rick for invisible Advance page
	m_tabPage.API_Init();
	m_tabPage.SetPadding(CSize(-2000, -2000));
	m_tabPage.SetItemSize(CSize(0, 0));
}


void CUSBControlDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此加入控制項告知處理常式程式碼
	*pResult = 0;
}


//Avoid that user press enter, the dialog will disappear
void CUSBControlDlg::OnOK()
{
	;
}
void CUSBControlDlg::OnBnClickedButton1Bowser()
{
	// TODO: Add your control notification handler code here

	OPENFILENAME  Dialog;				        //Dialog struct
	TCHAR		  szFile[1024] = TEXT("\0");	//File Name buffer　　　　　　　　　

	//Initial Dialog
	ZeroMemory(&Dialog,  sizeof(OPENFILENAME) );
	Dialog.lStructSize = sizeof(OPENFILENAME);
	Dialog.hwndOwner   = m_hWnd;
	Dialog.lpstrFile   = szFile;

	Dialog.lpstrFile[0]    = _T('\0');
	Dialog.nMaxFile        = sizeof(szFile)/sizeof(TCHAR);
	Dialog.lpstrFilter     = _T("Bin\0*.bin\0All Files\0*.*\0");
	Dialog.nFilterIndex    = 1;
	Dialog.lpstrFileTitle  = NULL;
	Dialog.nMaxFileTitle   = 0;
	Dialog.lpstrInitialDir = NULL;
	Dialog.Flags           = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	//Show dialog
	if( GetOpenFileName(&Dialog) )
	{
		m_strFilePath = szFile;

		//Show Path to edit box
		this->GetDlgItem(IDC_EDIT3_PATH)->SetWindowText(m_strFilePath);
		//MessageBox(m_strFilePath,"File Path",MB_OK);
	}
}
