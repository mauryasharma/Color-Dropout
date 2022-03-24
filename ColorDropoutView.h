// ColorDropoutView.h : interface of the CColorDropoutView class
//

#pragma once
#include "ColorDrop.h"
enum SIZES		{ SIZE_QUARTER, SIZE_HALF, SIZE_ORIGINAL, SIZE_DOUBLE, SIZE_FILL, SIZE_NONE };

class CColorDropoutView : public CScrollView
{
	COLORREF RED, GREEN, BLUE, WHITE, BLACK;
	CColorDrop colorDrop;
	int m_Color;
	int m_Convert;
	int m_Intensity;

	CImage m_Image;

	CDC*	m_pDC;
	CBitmap* m_pBitmap;
	CSize size;

	int	m_nFilterLoad;
	SIZES m_nImageSize;
	CRect m_Rect;
	CRect m_SelRect;
protected: // create from serialization only
	CColorDropoutView();
	DECLARE_DYNCREATE(CColorDropoutView)

// Attributes
public:
	CColorDropoutDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	//virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	//virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CColorDropoutView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT OnUserApply(WPARAM wParam, LPARAM lParam);
	virtual void OnInitialUpdate();
	afx_msg void OnPaint();
	afx_msg void OnFileColordrop();
	afx_msg void OnZoom25();
	afx_msg void OnZoom50();
	afx_msg void OnZoom100();
	afx_msg void OnZoom200();
	afx_msg void OnZoomFill();

	void Image_Load(LPCTSTR lpszPathName);	
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in ColorDropoutView.cpp
inline CColorDropoutDoc* CColorDropoutView::GetDocument() const
   { return reinterpret_cast<CColorDropoutDoc*>(m_pDocument); }
#endif

