// ColorDropout.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ColorDropout.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "ColorDropoutDoc.h"
#include "ColorDropoutView.h"
#include ".\colordropout.h"
#include "ColorDrop.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CColorDropoutApp
CScrollView *g_pView;
BEGIN_MESSAGE_MAP(CColorDropoutApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	// Standard file based document commands
	// Standard print setup command
	ON_COMMAND(ID_FILE_OPENIMAGE, OnFileOpenimage)
END_MESSAGE_MAP()


// CColorDropoutApp construction

CColorDropoutApp::CColorDropoutApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CColorDropoutApp object

CColorDropoutApp theApp;

// CColorDropoutApp initialization

BOOL CColorDropoutApp::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_ColorDropoutTYPE,
		RUNTIME_CLASS(CColorDropoutDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CColorDropoutView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;
	
	// call DragAcceptFiles only if there's a suffix
	//m_pMainWnd->DragAcceptFiles(TRUE);
	//  In an MDI app, this should occur immediately after setting m_pMainWnd
	// Parse command line for standard shell commands, DDE, file open
	//CCommandLineInfo cmdInfo;
	//ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	//if (!ProcessShellCommand(cmdInfo))
	//	return FALSE;
	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
	return TRUE;
}



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
public:
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	SetDlgItemText(IDC_TEXT,"Developed as test project for checking color dropout facility for the form processing system. The idea is to scan a colored form and then remove the boundary of the form field by Color Dropout technique. From the CColorDrop class just call the function DropColor(COLORREF color, int iType,int Intensity), color is the color to be dropped, Type is whether convertion to be made to monochrome or to grayscale and Intensity is for grayscale, whether light, medium or dark grayscales are to be used.");

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

// App command to run the dialog
void CColorDropoutApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CColorDropoutApp message handlers


void CColorDropoutApp::OnFileOpenimage()
{
	// TODO: Add your command handler code here
	CString strFilter;
	HRESULT hResult;
	
	CImage m_Image;
	strFilter = "Image Files (*.tif;*.tiff;*.bmp;*.dib;*.gif;*.jpg;*.jpeg;*.jpe;*.jfif;*.png;*.rle)|*.tif;*.tiff;*.bmp;*.dib;*.gif;*.jpg;*.jpeg;*.jpe;*.jfif;*.png;*.rle||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, strFilter);
	hResult = (int)dlg.DoModal();
	if(hResult != IDOK) {
		return;
	}
	else
	{
		POSITION curTemplatePos = GetFirstDocTemplatePosition();
		while(curTemplatePos != NULL)
		{
			CDocTemplate* curTemplate = GetNextDocTemplate(curTemplatePos);
			CString str;
			curTemplate->GetDocString(str, CDocTemplate::docName);
			if (str == _T("ColorDropout"))
			{
				curTemplate->OpenDocumentFile(dlg.GetPathName(), TRUE);
				return;
			}
		}
	}
}
