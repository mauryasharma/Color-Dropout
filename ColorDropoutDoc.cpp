// ColorDropoutDoc.cpp : implementation of the CColorDropoutDoc class
//

#include "stdafx.h"
#include "ColorDropout.h"

#include "ColorDropoutDoc.h"
#include ".\colordropoutdoc.h"
#include "ColorDropoutView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CColorDropoutDoc

IMPLEMENT_DYNCREATE(CColorDropoutDoc, CDocument)

BEGIN_MESSAGE_MAP(CColorDropoutDoc, CDocument)
END_MESSAGE_MAP()


// CColorDropoutDoc construction/destruction

CColorDropoutDoc::CColorDropoutDoc()
{
	// TODO: add one-time construction code here

}

CColorDropoutDoc::~CColorDropoutDoc()
{
}

BOOL CColorDropoutDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

// CColorDropoutDoc serialization

void CColorDropoutDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CColorDropoutDoc diagnostics

#ifdef _DEBUG
void CColorDropoutDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CColorDropoutDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CColorDropoutDoc commands

BOOL CColorDropoutDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  Add your specialized creation code here
	POSITION pos = GetFirstViewPosition();
	CColorDropoutView* pView = (CColorDropoutView*)GetNextView(pos);
	pView->Image_Load(lpszPathName);
	return TRUE;
}

BOOL CColorDropoutDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: Add your specialized code here and/or call the base class

	AfxMessageBox("Can't save the document");
	return true;
	//return CDocument::OnSaveDocument(lpszPathName);
}
