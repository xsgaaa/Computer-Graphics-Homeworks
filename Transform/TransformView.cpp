// TransformView.cpp : implementation of the CTransformView class
//

#include "stdafx.h"
#include "Transform.h"
#include<windows.h>
#include "TransformDoc.h"
#include "TransformView.h"
#include "MainFrm.h"
#include<cmath>
#define PI 3.14159
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransformView

IMPLEMENT_DYNCREATE(CTransformView, CView)

BEGIN_MESSAGE_MAP(CTransformView, CView)
	//{{AFX_MSG_MAP(CTransformView)
	ON_COMMAND(ID_DRAWLINE, OnDrawline)
	ON_COMMAND(ID_DRAWPOLYGON, OnDrawpolygon)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_LINE, OnLine)
	ON_COMMAND(ID_POLYGON, OnPolygon)
	ON_COMMAND(ID_STOP, OnStop)
	ON_COMMAND(ID_CHOOSELINE, OnChooseline)
	ON_COMMAND(ID_CHOOSEPOLYGON, OnChoosepolygon)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_SYM, OnSym)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransformView construction/destruction

CTransformView::CTransformView()
{
	shape=1;
	linecount=0;
	count=0;
	IsEnd=true;
	choose=false;
	choose1=false;
	current=-1;
	current1=-1;
	sym=false;
	flag=0;
}

CTransformView::~CTransformView()
{
}

BOOL CTransformView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTransformView drawing

 void CTransformView::OnDraw(CDC* pDC)
{
	CTransformDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CPen pen(0,3,RGB(0,0,255));
	CPen *oldpen=pDC->SelectObject(&pen);
	pDC->MoveTo(Line[0].x,Line[0].y);
	pDC->LineTo(Line[1].x,Line[1].y);

	pDC->TextOut(0,0,"图形的操作:");
	pDC->TextOut(0,20,"1,左键移动操作(↑↓←→也可)");
	pDC->TextOut(0,40,"2,右键旋转操作");
	pDC->TextOut(0,60,"3,滑轮放缩操作");
	pDC->TextOut(0,80,"4,点击按钮<对称>,进行对称操作");

	if(!IsEnd)
	{
		if(count!=0)
		{
			CPen pen(0,3,RGB(255,255,0));
			CPen *oldpen=pDC->SelectObject(&pen);
			for(int i=0;i<count-1;i++)   
			{
				pDC->MoveTo(polygon[i].x,polygon[i].y);
				pDC->LineTo(polygon[i+1].x,polygon[i+1].y); 
			}
			pDC->MoveTo(polygon[0].x,polygon[0].y);
			pDC->LineTo(polygon[count-1].x,polygon[count-1].y);
			pDC->SelectObject(&oldpen);
		}
	}
	CBrush bru,*oldbru;
	bru.CreateSolidBrush(RGB(230,64,225));
	oldbru=pDC->SelectObject(&bru);
	if(choose)
	{
		pDC->Rectangle(Line[0].x-5,Line[0].y+5,Line[0].x+5,Line[0].y-5);
		pDC->Rectangle(Line[1].x-5,Line[1].y+5,Line[1].x+5,Line[1].y-5);
	}
	if(choose1)
	{
		for(int i=0;i<count;i++)
		{
			pDC->Rectangle(polygon[i].x-5,polygon[i].y+5,polygon[i].x+5,polygon[i].y-5);
		}
	}
	pDC->SelectObject(oldbru);
}

/////////////////////////////////////////////////////////////////////////////
// CTransformView printing

BOOL CTransformView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTransformView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTransformView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTransformView diagnostics

#ifdef _DEBUG
void CTransformView::AssertValid() const
{
	CView::AssertValid();
}

void CTransformView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTransformDoc* CTransformView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTransformDoc)));
	return (CTransformDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTransformView message handlers

void CTransformView::OnDrawline() 
{
	shape=1;
	linecount=0;
}

void CTransformView::OnDrawpolygon() 
{
	shape=2;
	count=0;
	IsEnd=true;
}

void CTransformView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(sym)
	{
		line[0]=line[1]=point;
	}
	else
	{
		if(shape==1)
		{
			if(linecount==0)
				Line[0]=point;
			if(linecount==1)
			{
				Line[1]=point;
				Invalidate();
			}
			linecount++;
		}
		if(shape==2)
		{
			if(IsEnd)
			{
				CDC *pDC=GetDC();
				CPen pen(0,3,RGB(255,255,0));
				CPen *oldpen=pDC->SelectObject(&pen);
				polygon[count].x=point.x;
				polygon[count].y=point.y;
				count++;
				if(count>=2)
				{
					pDC->MoveTo(polygon[count-2].x,polygon[count-2].y);
					pDC->LineTo(polygon[count-1].x,polygon[count-1].y);
				}
				pDC->SelectObject(oldpen);
				ReleaseDC(pDC);
			}
		}
		if(choose)
		{
			double x,y,t;
			t=50;
			for(int i=0;i<2;i++)
			{
				x=(Line[i].x-point.x)*(Line[i].x-point.x);
				y=(Line[i].y-point.y)*(Line[i].y-point.y);
				if(x+y<t)
				{
					current=i;	
					t=x+y;	
				}
			}
		}
		if(choose1&&!choose)
		{
			double x,y,t;
			t=50;
			for(int i=0;i<count;i++)
			{
				x=(polygon[i].x-point.x)*(polygon[i].x-point.x);
				y=(polygon[i].y-point.y)*(polygon[i].y-point.y);
				if(x+y<t)
				{
					current1=i;	
					t=x+y;	
				}
			}
		}
	}
	CView::OnLButtonDown(nFlags, point);
}

void CTransformView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	current=-1;
	current1=-1;
	CDC *pDC=GetDC();
	CPen pen(0,3,RGB(0,0,0));
	pDC->SelectObject(&pen);
	if(!IsEnd)//重画多边形是避免重绘
	{
		if(choose)
		{
			if(sym)
			{	
				CPoint pt[2];
				if(line[0].x==line[1].x)//考虑x=b时的情况
				{
					for(int i=0;i<2;i++)
					{
						Line[i].x+=2*(line[0].x-Line[i].x);
						pt[i]=Line[i];
					}
				}
				else
				{
					for(int i=0;i<2;i++)
						pt[i]=Line[i]=SymPoint(Line[i],line[0],line[1]);
				}
				pDC->MoveTo(pt[0]);
				pDC->LineTo(pt[1]);
				Sleep(1000);
			}
			Invalidate();
			sym=false;
			CPoint a;
			line[0]=a;
			line[1]=a;
		}
		if(choose1&&!choose)
		{
			if(sym)
			{
				CPoint pt[MAX];
				if(line[0].x==line[1].x)//考虑x=b的情况
				{
					for(int i=0;i<count;i++)
					{
						polygon[i].x+=2*(line[0].x-polygon[i].x);
						pt[i]=polygon[i];
					}
				}
				else
				{
					for(int i=0;i<count;i++)
						pt[i]=polygon[i]=SymPoint(polygon[i],line[0],line[1]);
				}
				for(int i=0;i<count-1;i++)   
				{
					pDC->MoveTo(pt[i].x,pt[i].y);
					pDC->LineTo(pt[i+1].x,pt[i+1].y); 
				}
				pDC->MoveTo(pt[0].x,pt[0].y);
				pDC->LineTo(pt[count-1].x,pt[count-1].y);
				Sleep(1000);
			}
			Invalidate();
			sym=false;
			CPoint a;
			line[0]=a;
			line[1]=a;
		}
	}
	CView::OnLButtonUp(nFlags, point);
}

void CTransformView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if(choose)
	{
		double x,y,t;
		t=50;
		for(int i=0;i<2;i++)
		{
			x=(Line[i].x-point.x)*(Line[i].x-point.x);
			y=(Line[i].y-point.y)*(Line[i].y-point.y);
			if(x+y<t)
			{
				current=i;	
				t=x+y;	
			}
		}
	}
	if(choose1&&!choose)
	{
		double x,y,t;
		t=50;
		for(int i=0;i<count;i++)
		{
			x=(polygon[i].x-point.x)*(polygon[i].x-point.x);
			y=(polygon[i].y-point.y)*(polygon[i].y-point.y);
			if(x+y<t)
			{
				current1=i;	
				t=x+y;	
			}
		}
	}
	CView::OnRButtonDown(nFlags, point);
}

void CTransformView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	current=-1;
	current1=-1;
	CView::OnRButtonUp(nFlags, point);
}
void CTransformView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);
	if(sym)
	{
		if(MK_LBUTTON==nFlags)
		{
			dc.SetROP2(R2_NOT);
			dc.MoveTo(line[0]);
			dc.LineTo(line[1]);
			line[1] = point;
			dc.MoveTo(line[0]);
			dc.LineTo(line[1]);
		}
	}
	else
	{
		if(choose&&current!=-1)
		{
			if(MK_LBUTTON == nFlags)
			{
				double dx,dy;
				dx=point.x-Line[current].x;
				dy=point.y-Line[current].y;
				for(int i=0;i<2;i++)
				{
					Line[i].x+=long(dx);
					Line[i].y+=long(dy);
				}
				Invalidate();
			}
			if(MK_RBUTTON == nFlags)
			{
				double dx,dy,Sin,Cos;
				dx=point.x-Line[current].x;
				dy=point.y-Line[current].y;
				Cos=cos(sqrt(dx*dx+dy*dy)*PI/180);
				Sin=sin(sqrt(dx*dx+dy*dy)*PI/180);
				CPoint temp=Line[current];
				for(int i=0;i<2;i++)
				{
					CPoint p=Line[i];
					Line[i].x=p.x*Cos-p.y*Sin;
					Line[i].y=p.x*Sin+p.y*Cos;
				}
				CPoint p1=Line[current];
				for(i=0;i<2;i++)
				{
					Line[i].x-=p1.x-temp.x;
					Line[i].y-=p1.y-temp.y;
				}//*/
				Invalidate();
			}
		}
		if(choose1&&!choose&&current1!=-1)
		{
			if(MK_LBUTTON == nFlags)
			{
				double dx,dy;
				dx=point.x-polygon[current1].x;
				dy=point.y-polygon[current1].y;
				for(int i=0;i<count;i++)
				{
					polygon[i].x+=long(dx);
					polygon[i].y+=long(dy);
				}
				Invalidate();
			}
			if(MK_RBUTTON == nFlags)
			{
				double dx,dy,Sin,Cos;
				dx=point.x-polygon[current1].x;
				dy=point.y-polygon[current1].y;
				Cos=cos(sqrt(dx*dx+dy*dy)*PI/180);
				Sin=sin(sqrt(dx*dx+dy*dy)*PI/180);
				CPoint temp=polygon[current1];
				for(int i=0;i<count;i++)
				{
					CPoint p=polygon[i];
					polygon[i].x=p.x*Cos-p.y*Sin;
					polygon[i].y=p.x*Sin+p.y*Cos;
				}
				CPoint p1=polygon[current1];
				for(i=0;i<count;i++)
				{
					polygon[i].x-=p1.x-temp.x;
					polygon[i].y-=p1.y-temp.y;
				}//*/
				Invalidate();
			}
		}
	}
	CView::OnMouseMove(nFlags, point);
}

void CTransformView::OnLine() 
{
	linecount=0;
	shape=1;
}

void CTransformView::OnPolygon() 
{
	shape=2;
	count=0;
	IsEnd=true;
}

void CTransformView::OnStop() 
{
	IsEnd=false;
	Invalidate();
}

void CTransformView::OnChooseline() 
{
	choose=true;
	choose1=false;
	current=-1;
	Invalidate();
}

void CTransformView::OnChoosepolygon() 
{
	choose1=true;
	choose=false;
	current1=-1;
	Invalidate();
}

BOOL CTransformView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) //放缩变换
{
	double scale=0;
	if(zDelta>0)
		scale=4/3.0;
	else
		scale=0.75;
	if(choose)//针对直线
	{	
		double zx,zy,zx1,zy1;
		zx=(Line[0].x+Line[1].x)/2;  
		zy=(Line[0].y+Line[1].y)/2;
		for(int i=0;i<2;i++)
		{
			Line[i].x=Line[i].x*scale;
			Line[i].y=Line[i].y*scale;
		}
		zx1=(Line[0].x+Line[1].x)/2;
		zy1=(Line[0].y+Line[1].y)/2;
		for(i=0;i<2;i++)
		{
			Line[i].x-=zx1-zx;
			Line[i].y-=zy1-zy;
		}

		Invalidate();
	}
	if(choose1&&!choose)
	{
		CPoint GravityCenter1,GravityCenter2;
		GravityCenter1=GravityCenter(count,polygon);
		for(int i=0;i<count;i++)
		{
			polygon[i].x=polygon[i].x*scale;
			polygon[i].y=polygon[i].y*scale;
		}
		GravityCenter2=GravityCenter(count,polygon);
		for(i=0;i<count;i++)
		{
			polygon[i].x-=GravityCenter2.x-GravityCenter1.x;
			polygon[i].y-=GravityCenter2.y-GravityCenter1.y;
		}
		Invalidate();
	}
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CTransformView::OnSym() 
{
	sym=true;
	MessageBox("请画一条线!","提示");
}

CPoint CTransformView::SymPoint(CPoint p, CPoint p1, CPoint p2)
{
	double k,b;
	k=(p2.y-p1.y)/double(p2.x-p1.x);
	b=p2.y-k*p2.x;
	CPoint ans;
	ans.y=(2*k*p.x+(k*k-1)*p.y+2*b)/double(k*k+1);
	ans.x=p.x-k*(ans.y-p.y);
	return ans;
}

CPoint CTransformView::GravityCenter(int vcount, CPoint polygon[])//多边形重心
{
	CPoint tp;
	double x,y,s,x0,y0,cs,k;
	x=0;y=0;s=0;
	for(int i=1;i<vcount-1;i++)
	{
		x0=(polygon[0].x+polygon[i].x+polygon[i+1].x)/3;
		y0=(polygon[0].y+polygon[i].y+polygon[i+1].y)/3; //求当前三角形的重心
		cs=multiply(polygon[i],polygon[i+1],polygon[0])/2;//三角形面积可以直接利用该公式求解
		if(abs(s)<1e-20)
		{
			x=x0;y=y0;s+=cs;continue;
		}
		k=cs/s; //求面积比例
		x=(x+k*x0)/(1+k);
		y=(y+k*y0)/(1+k);
		s += cs;
	}
	tp.x=x;
	tp.y=y;
	return tp;
}
void CTransformView::Calculate(double P0[][3],double T[][3])//两个矩阵相乘
{
	
}
double CTransformView::multiply(CPoint sp, CPoint ep, CPoint op)//求三角形面积
{
	return((sp.x-op.x)*(ep.y-op.y) - (ep.x-op.x)*(sp.y-op.y));
}

void CTransformView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{	
	if(choose)
	{
		if(VK_LEFT == nChar)
		{
			for(int i=0;i<2;i++)
				Line[i].x-=1;
		}
		if(VK_RIGHT == nChar)
		{
			for(int i=0;i<2;i++)
				Line[i].x+=1;
		}
		if(VK_UP == nChar)
		{
			for(int i=0;i<2;i++)
				Line[i].y-=1;
		}
		if(VK_DOWN == nChar)
		{
			for(int i=0;i<2;i++)
				Line[i].y+=1;
		}
		Invalidate();
	}
	if(choose1&&!choose)
	{
		if(VK_LEFT == nChar)
		{
			for(int i=0;i<count;i++)
				polygon[i].x-=1;
		}
		if(VK_RIGHT == nChar)
		{
			for(int i=0;i<count;i++)
				polygon[i].x+=1;
		}
		if(VK_UP == nChar)
		{
			for(int i=0;i<count;i++)
				polygon[i].y-=1;
		}
		if(VK_DOWN == nChar)
		{
			for(int i=0;i<count;i++)
				polygon[i].y+=1;
		}
		Invalidate();
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
