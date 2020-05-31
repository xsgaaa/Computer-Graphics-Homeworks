// TransformView.h : interface of the CTransformView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSFORMVIEW_H__3B71386C_3C70_4F39_B92C_A20BB0537A5F__INCLUDED_)
#define AFX_TRANSFORMVIEW_H__3B71386C_3C70_4F39_B92C_A20BB0537A5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX 50 
class CTransformView : public CView
{
protected: // create from serialization only
	CTransformView();
	DECLARE_DYNCREATE(CTransformView)

// Attributes
public:
	CTransformDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransformView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	double multiply(CPoint sp,CPoint ep,CPoint op);
	CPoint GravityCenter(int vcount,CPoint polygon[]);
	void Calculate(double P0[][3],double T[][3]);
	CPoint SymPoint(CPoint p,CPoint p1,CPoint p2);
	CPoint line[2];
	int flag;
	bool sym;
	int current1;
	int current;
	bool choose;
	bool choose1;
	bool IsEnd;
	CPoint Line[2];
	CPoint polygon[MAX];
	int count;
	int linecount;
	int shape;
	
	virtual ~CTransformView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTransformView)
	afx_msg void OnDrawline();
	afx_msg void OnDrawpolygon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLine();
	afx_msg void OnPolygon();
	afx_msg void OnStop();
	afx_msg void OnChooseline();
	afx_msg void OnChoosepolygon();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSym();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TransformView.cpp
inline CTransformDoc* CTransformView::GetDocument()
   { return (CTransformDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSFORMVIEW_H__3B71386C_3C70_4F39_B92C_A20BB0537A5F__INCLUDED_)
