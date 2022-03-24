#pragma once
#include "afxwin.h"


// CColorDrop dialog
extern CScrollView *g_pView;
#define WM_USERAPPLY WM_USER + 5

class CColorDrop : public CDialog
{
	DECLARE_DYNAMIC(CColorDrop)

public:
	COLORREF RED, GREEN, BLUE, WHITE, BLACK;
	int m_Color;
	int m_Convert;
	int m_Intensity;
	CColorDrop(CWnd* pParent = NULL);   // standard constructor
	virtual ~CColorDrop();

// Dialog Data
	enum { IDD = IDD_COLORDROP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CButton m_Apply;
	afx_msg void OnBnClickedApply();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	void ConvertImage(CImage &m_Image,COLORREF color,int convert, int intensity);
	void PumpMessages();

	afx_msg void OnBnClickedGray();
	afx_msg void OnBnClickedMono();
	afx_msg void OnBnClickedColored();
	CButton m_Ok;
	CButton m_Cancel;
};
