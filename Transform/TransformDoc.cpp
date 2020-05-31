// TransformDoc.cpp : implementation of the CTransformDoc class
//

#include "stdafx.h"
#include "Transform.h"

#include "TransformDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransformDoc

IMPLEMENT_DYNCREATE(CTransformDoc, CDocument)

BEGIN_MESSAGE_MAP(CTransformDoc, CDocument)
	//{{AFX_MSG_MAP(CTransformDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransformDoc construction/destruction

CTransformDoc::CTransformDoc()
{
	// TODO: add one-time construction code here

}

CTransformDoc::~CTransformDoc()
{
}

BOOL CTransformDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTransformDoc serialization

void CTransformDoc::Serialize(CArchive& ar)
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

/////////////////////////////////////////////////////////////////////////////
// CTransformDoc diagnostics

#ifdef _DEBUG
void CTransformDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTransformDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTransformDoc commands
