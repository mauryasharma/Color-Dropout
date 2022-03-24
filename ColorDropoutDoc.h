// ColorDropoutDoc.h : interface of the CColorDropoutDoc class
//


#pragma once

class CColorDropoutDoc : public CDocument
{
protected: // create from serialization only
	CColorDropoutDoc();
	DECLARE_DYNCREATE(CColorDropoutDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CColorDropoutDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
};


