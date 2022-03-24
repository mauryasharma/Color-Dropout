// ColorDropoutView.cpp : implementation of the CColorDropoutView class
//

#include "stdafx.h"
#include "ColorDropout.h"
#include "MainFrm.h"


#include "ColorDropoutDoc.h"
#include "ColorDropoutView.h"
#include ".\colordropoutview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CColorDropoutView

IMPLEMENT_DYNCREATE(CColorDropoutView, CScrollView)

BEGIN_MESSAGE_MAP(CColorDropoutView, CScrollView)
	// Standard printing commands
	//ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	//ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	//ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
	ON_MESSAGE(WM_USERAPPLY, OnUserApply)
	ON_WM_PAINT()
	ON_COMMAND(ID_FILE_COLORDROP, OnFileColordrop)
	ON_COMMAND(ID_ZOOM_25, OnZoom25)
	ON_COMMAND(ID_ZOOM_50, OnZoom50)
	ON_COMMAND(ID_ZOOM_100, OnZoom100)
	ON_COMMAND(ID_ZOOM_200, OnZoom200)
	ON_COMMAND(ID_ZOOM_FILL, OnZoomFill)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CColorDropoutView construction/destruction

CColorDropoutView::CColorDropoutView()
{
	// TODO: add construction code here	
	WHITE = RGB(255,255,255);
	BLACK = RGB(0,0,0);
	RED = RGB(255,0,0);
	GREEN = RGB(0,255,0);
	BLUE = RGB(0,0,255);
	g_pView = this;
	m_pDC = new CDC;
	m_pBitmap = new CBitmap;

	m_nImageSize = SIZE_ORIGINAL;
}

CColorDropoutView::~CColorDropoutView()
{
}

BOOL CColorDropoutView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// CColorDropoutView drawing

void CColorDropoutView::OnDraw(CDC* /*pDC*/)
{
	CColorDropoutDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CColorDropoutView printing

//BOOL CColorDropoutView::OnPreparePrinting(CPrintInfo* pInfo)
//{
	// default preparation
//	return DoPreparePrinting(pInfo);
//}

//void CColorDropoutView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
//{
	// TODO: add extra initialization before printing
//}

//void CColorDropoutView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
//{
	// TODO: add cleanup after printing
//}


// CColorDropoutView diagnostics

#ifdef _DEBUG
void CColorDropoutView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CColorDropoutView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CColorDropoutDoc* CColorDropoutView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CColorDropoutDoc)));
	return (CColorDropoutDoc*)m_pDocument;
}
#endif //_DEBUG


// CColorDropoutView message handlers
void CColorDropoutView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: calculate the total size of this view
	if (!m_Image.IsNull())
	{
		size.cx = m_Image.GetWidth();
		size.cy = m_Image.GetHeight();
	}
	else
	{
		size.cx = 1000;
		size.cy = 1000;
	}
	SetScrollSizes(MM_TEXT, size);
	CBitmap* pOldBitmap;
	CDC* pDC;
	pDC = GetDC();

	m_pDC->CreateCompatibleDC(pDC);
	m_pDC->SetMapMode(MM_TEXT);
	m_pBitmap->CreateBitmap(size.cx, size.cy, 1, 1, NULL);
	
	pOldBitmap = m_pDC->SelectObject(m_pBitmap);

	OnDraw(m_pDC);

	m_pDC->SelectObject(pOldBitmap);
	ReleaseDC(pDC);
}

void CColorDropoutView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CScrollView::OnPaint() for painting messages
	CDC MemDC;
	//CBitmap* pOldBitmap;
	CSize size;
	OnPrepareDC(&dc);
	size = GetTotalSize();
	MemDC.CreateCompatibleDC(&dc);

	if (!m_Image.IsNull()) 
	{
		CRect rctWindowSize;
		double factor=0.0;
		switch (m_nImageSize)
		{
			case SIZE_QUARTER:
				m_Image.StretchBlt(dc,0,0,m_Image.GetWidth()/4,m_Image.GetHeight()/4,SRCCOPY);
				factor = .25;
				break;
			case SIZE_HALF:
				m_Image.StretchBlt(dc,0,0,m_Image.GetWidth()/2,m_Image.GetHeight()/2,SRCCOPY);
				factor = 0.5;
				break;
			case SIZE_ORIGINAL:
				m_Image.StretchBlt(dc,0,0,m_Image.GetWidth(),m_Image.GetHeight(),SRCCOPY);
				factor = 1.0;
				break;
			case SIZE_DOUBLE:
				m_Image.StretchBlt(dc,0,0,m_Image.GetWidth()*2,m_Image.GetHeight()*2,SRCCOPY);
				factor = 2.0;
				break;
			case SIZE_FILL:				
				GetClientRect(rctWindowSize);
				m_Image.StretchBlt(dc,0,0,rctWindowSize.Width(),rctWindowSize.Height(),SRCCOPY);
		}
		CSize size;
		if (factor > 0.0)
		{
			size.cx = (long)(m_Image.GetWidth()*factor);
			size.cy = (long)(m_Image.GetHeight()*factor);
		}
		else
		{
			size.cx = rctWindowSize.Width();
			size.cy = rctWindowSize.Height();
		}

		SetScrollSizes(MM_TEXT, size);		
	}
	CBrush br(WHITE);//GetSysColor( COLOR_WINDOWFRAME ) ); 
	FillOutsideRect( GetDC(), &br );
}

void CColorDropoutView::OnZoom25()
{
	// TODO: Add your command handler code here
	m_nImageSize = SIZE_QUARTER;
	Invalidate();
	UpdateWindow();
}

void CColorDropoutView::OnZoom50()
{
	// TODO: Add your command handler code here
	m_nImageSize = SIZE_HALF;
	Invalidate();
	UpdateWindow();
}

void CColorDropoutView::OnZoom100()
{
	// TODO: Add your command handler code here
	m_nImageSize = SIZE_ORIGINAL;
	Invalidate();
	UpdateWindow();
}

void CColorDropoutView::OnZoom200()
{
	// TODO: Add your command handler code here
	m_nImageSize = SIZE_DOUBLE;
	Invalidate();
	UpdateWindow();
}

void CColorDropoutView::OnZoomFill()
{
	// TODO: Add your command handler code here
	m_nImageSize = SIZE_FILL;
	Invalidate();
	UpdateWindow();
}

void CColorDropoutView::Image_Load(LPCTSTR lpszPathName)
{
	HRESULT hResult;
	m_Image.Destroy();
	hResult = m_Image.Load(lpszPathName);

	if (FAILED(hResult)) {
		CString fmt;
		fmt.Format("Load image failed");//:\n%x - %s", hResult, _com_error(hResult).ErrorMessage());
		::AfxMessageBox(fmt);
		return;
	}
	int m_nImageSize = SIZE_ORIGINAL;
	Invalidate();
	UpdateWindow();
}
void CColorDropoutView::OnFileColordrop()
{
	// TODO: Add your command handler code here
	if (colorDrop.DoModal() == IDCANCEL)
	{
		CColorDropoutDoc* pDoc = GetDocument();
		CString str = pDoc->GetPathName();
		pDoc->OnOpenDocument(str);
	}
}


LRESULT CColorDropoutView::OnUserApply(WPARAM wParam, LPARAM lParam)
{
	m_Color = colorDrop.m_Color;
	m_Convert = colorDrop.m_Convert;
	m_Intensity = colorDrop.m_Intensity;
	switch(m_Color)
	{
	case 1:
		colorDrop.ConvertImage(m_Image,RED,m_Convert,m_Intensity);		
		break;
	case 2:
		colorDrop.ConvertImage(m_Image,GREEN,m_Convert,m_Intensity);
		break;
	case 3:
		colorDrop.ConvertImage(m_Image,BLUE,m_Convert,m_Intensity);
		break;
	}
		
	Invalidate();
	UpdateWindow();
	//CDocument *pDoc = GetDocument();
	//pDoc->SetModifiedFlag();
    return 0;
}

void CColorDropoutView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.DPtoLP(&point);
	CString str;
	//CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	//CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	//if (pStatus)
	//{
	//	str.Format("X -> %d Y -> %d",point.x,point.y);
	//	pStatus->SetPaneText(1,str);
	//}
	CScrollView::OnMouseMove(nFlags, point);
}
