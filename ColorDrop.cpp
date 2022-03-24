// ColorDrop.cpp : implementation file
//

#include "stdafx.h"
#include "ColorDropout.h"
#include "ColorDrop.h"
#include ".\colordrop.h"


// CColorDrop dialog

IMPLEMENT_DYNAMIC(CColorDrop, CDialog)
CColorDrop::CColorDrop(CWnd* pParent /*=NULL*/)
	: CDialog(CColorDrop::IDD, pParent)
{
	WHITE = RGB(255,255,255);
	BLACK = RGB(0,0,0);
	RED = RGB(255,0,0);
	GREEN = RGB(0,255,0);
	BLUE = RGB(0,0,255);
	m_Color = 0;
}

CColorDrop::~CColorDrop()
{
}

void CColorDrop::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_APPLY, m_Apply);
	DDX_Control(pDX, IDOK, m_Ok);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
}


BEGIN_MESSAGE_MAP(CColorDrop, CDialog)
	ON_BN_CLICKED(IDC_APPLY, OnBnClickedApply)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_GRAY, OnBnClickedGray)
	ON_BN_CLICKED(IDC_MONO, OnBnClickedMono)
	ON_BN_CLICKED(IDC_COLORED, OnBnClickedColored)
END_MESSAGE_MAP()


// CColorDrop message handlers
BOOL CColorDrop::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CheckDlgButton(IDC_RED,1);
	CheckDlgButton(IDC_MONO,1);
	CheckDlgButton(IDC_LIGHT,1);

	GetDlgItem(IDC_LIGHT)->EnableWindow(false);
	GetDlgItem(IDC_MEDIUM)->EnableWindow(false);
	GetDlgItem(IDC_DARK)->EnableWindow(false);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CColorDrop::OnBnClickedApply()
{
	// TODO: Add your control notification handler code here
	m_Apply.EnableWindow(false);
	m_Ok.EnableWindow(false);
	m_Cancel.EnableWindow(false);
	m_Color = 1;
	if (IsDlgButtonChecked(IDC_RED))
		m_Color = 1;
	else
		if (IsDlgButtonChecked(IDC_GREEN))
			m_Color = 2;
		else
			if (IsDlgButtonChecked(IDC_BLUE))
				m_Color = 3;

	m_Convert = 1;
	if (IsDlgButtonChecked(IDC_MONO))
		m_Convert = 1;
	else
		if (IsDlgButtonChecked(IDC_GRAY))
			m_Convert = 2;
		else
			if (IsDlgButtonChecked(IDC_COLORED))
				m_Convert = 3;

	m_Intensity = 1;
	if (IsDlgButtonChecked(IDC_LIGHT))
		m_Intensity = 1;
	else
		if (IsDlgButtonChecked(IDC_MEDIUM))
			m_Intensity = 2;
		else
			if (IsDlgButtonChecked(IDC_DARK))
				m_Intensity = 3;

	g_pView->SendMessage(WM_USERAPPLY);
	m_Apply.EnableWindow();
	m_Ok.EnableWindow();
	m_Cancel.EnableWindow();	
}

void CColorDrop::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//OnBnClickedApply();
	OnOK();
}

void CColorDrop::ConvertImage(CImage &m_Image,COLORREF color,int convert, int intensity)
{
	register long x,y,w,h;
	register int min,max,mid;
				
	COLORREF c;
	BYTE rvalue,gvalue,bvalue;
	w = m_Image.GetWidth();
	h = m_Image.GetHeight();

/*	//DWORD DropColors[THRESHOLD*THRESHOLD];

	if (m_Image.IsDIBSection())
	{
		int BPP;
		BPP = m_Image.GetBPP();
	
#undef PXTYPE
	switch (BPP)
	{
	case 1:
	case 4:
	case 8:
#ifndef PXTYPE
	#define PXTYPE BYTE
#endif
		//AfxMessageBox("1");
		break;
	case 16:
#ifndef PXTYPE
	#define PXTYPE unsigned short int
#endif
		//AfxMessageBox("16");
		break;
	case 24:
#ifndef PXTYPE
	#define PXTYPE unsigned int
#endif
		//AfxMessageBox("32");
		break;
	default:
#ifndef PXTYPE
	#define PXTYPE unsigned int
#endif
		//AfxMessageBox("32");
		break;
	}
	
	PXTYPE *Img;
	
	DWORD mw,nw,tt=0,isize = m_Image.GetWidth()*m_Image.GetHeight();

	Img = new PXTYPE[isize];
	Img = (PXTYPE *)m_Image.GetBits();
		
	do{
		mw = Img[tt];
		mw >>= 8;
		nw = Img[tt] << 24;
		tt++;
	}while (tt < isize);
	*/
	for (y = 0;y < h;y++)
	{
		for (x = 0;x < w;x++)
		{
			//if (x == 72 && y == 483)
			//	AfxMessageBox("Hello");
			c = m_Image.GetPixel(x,y);
			rvalue = GetRValue(c);
			gvalue = GetGValue(c);
			bvalue = GetBValue(c);
			switch (convert)
			{
			case 1:
				if (color == RED)
				{
					if (rvalue > 180)
					{
						rvalue = gvalue = bvalue = 255;
					}
					else
					{
						rvalue = gvalue = bvalue = 0;
					}
				}
				else
				{
					if (color == GREEN)
					{
						if (gvalue > 180)
						{
							rvalue = gvalue = bvalue = 255;
						}
						else
						{
							rvalue = gvalue = bvalue = 0;
						}
					}
					else
					{
						if (color == BLUE)
						{
							if (bvalue > 180)
							{
								rvalue = gvalue = bvalue = 255;
							}
							else
							{
								rvalue = gvalue = bvalue = 0;
							}
						}
					}
				}
				break;
			case 2:
				min= rvalue;
				max = rvalue;
				mid=255;
				
				if (max < gvalue)
					max = gvalue;
				if (max < bvalue)
                    max = bvalue;
				
				if (min > gvalue)
					min = gvalue;
				if (min > bvalue)
					min = bvalue;
				
				if ((min == rvalue && max == gvalue) || (min == gvalue && max == rvalue))
					mid = bvalue;
				if ((min == rvalue && max == bvalue) || (min == bvalue && max == rvalue))
					mid = gvalue;
				if ((min == gvalue && max == bvalue) || (min == bvalue && max == gvalue))
					mid = rvalue;

				if (intensity == 1)
                    rvalue = gvalue = bvalue = max;
				if (intensity == 2)
                    rvalue = gvalue = bvalue = mid;
				if (intensity == 3)
                    rvalue = gvalue = bvalue = min;
				break;
			case 3:
				if (color == RED)
				{
					//if (rvalue > 180)
						rvalue = 0;
				}
				else
				{
					if (color == GREEN)
					{
						//if (gvalue > 180)
							gvalue = 0;
					}
					else
					{
						if (color == BLUE)
						{
							//if (bvalue > 180)
								bvalue = 0;
						}
					}
				}
				break;
			}
			//c = RGB(rvalue,gvalue,bvalue);
			//m_Image.SetPixel(x,v,c);
			m_Image.SetPixelRGB(x,y,rvalue,gvalue,bvalue);;
		}
		PumpMessages();
	}
}


void CColorDrop::PumpMessages()
{
    // Must call Create() before using the dialog
    ASSERT(m_hWnd!=NULL);

    MSG msg;
    // Handle dialog messages
    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        if(!IsDialogMessage(&msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void CColorDrop::OnBnClickedGray()
{
	// TODO: Add your control notification handler code here
	if (IsDlgButtonChecked(IDC_GRAY))
	{
		GetDlgItem(IDC_LIGHT)->EnableWindow();
		GetDlgItem(IDC_MEDIUM)->EnableWindow();
		GetDlgItem(IDC_DARK)->EnableWindow();

		GetDlgItem(IDC_RED)->EnableWindow(false);
		GetDlgItem(IDC_GREEN)->EnableWindow(false);
		GetDlgItem(IDC_BLUE)->EnableWindow(false);
	}	
}

void CColorDrop::OnBnClickedMono()
{
	// TODO: Add your control notification handler code here
	if (IsDlgButtonChecked(IDC_MONO))
	{
		GetDlgItem(IDC_LIGHT)->EnableWindow(false);
		GetDlgItem(IDC_MEDIUM)->EnableWindow(false);
		GetDlgItem(IDC_DARK)->EnableWindow(false);

		GetDlgItem(IDC_RED)->EnableWindow();
		GetDlgItem(IDC_GREEN)->EnableWindow();
		GetDlgItem(IDC_BLUE)->EnableWindow();
	}
}

void CColorDrop::OnBnClickedColored()
{
	// TODO: Add your control notification handler code here
	if (IsDlgButtonChecked(IDC_COLORED))
	{
		GetDlgItem(IDC_LIGHT)->EnableWindow(false);
		GetDlgItem(IDC_MEDIUM)->EnableWindow(false);
		GetDlgItem(IDC_DARK)->EnableWindow(false);

		GetDlgItem(IDC_RED)->EnableWindow();
		GetDlgItem(IDC_GREEN)->EnableWindow();
		GetDlgItem(IDC_BLUE)->EnableWindow();
	}
}
