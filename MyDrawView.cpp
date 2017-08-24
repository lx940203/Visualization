// MyDrawView.cpp : implementation of the CMyDrawView class
//

#include "stdafx.h"
#include "MyDraw.h"

#include "GraphSeries.h"
#include "Graph.h"

#include "MyDrawDoc.h"
#include "MyDrawView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDrawView

IMPLEMENT_DYNCREATE(CMyDrawView, CView)

BEGIN_MESSAGE_MAP(CMyDrawView, CView)
	//{{AFX_MSG_MAP(CMyDrawView)
	ON_COMMAND(ID_DRAW_BAR, OnDrawBar)
	ON_COMMAND(ID_DRAW_LINE, OnDrawLine)
	ON_COMMAND(ID_DRAW_PIE, OnDrawPie)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDrawView construction/destruction

CMyDrawView::CMyDrawView()
{
	// TODO: add construction code here

}

CMyDrawView::~CMyDrawView()
{
}

BOOL CMyDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyDrawView drawing

void CMyDrawView::OnDraw(CDC* pDC)
{
	CMyDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if(graphComplete)
		MyGraph->DrawGraph(pDC);
	
	UpdateWindow();

}

/////////////////////////////////////////////////////////////////////////////
// CMyDrawView printing

BOOL CMyDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyDrawView diagnostics

#ifdef _DEBUG
void CMyDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CMyDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyDrawDoc* CMyDrawView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDrawDoc)));
	return (CMyDrawDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyDrawView message handlers

void CMyDrawView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	graphComplete = FALSE;
	
}

void CMyDrawView::OnDrawBar() 
{
	// TODO: Add your command handler code here


	DrawChart(0,"柱状图",100,400,15,"星期","营业额");	
}

void CMyDrawView::OnDrawLine() 
{
	// TODO: Add your command handler code here

	
	DrawChart(1,"曲线图",100,400,13,"日期","销售量");

		
}

void CMyDrawView::OnDrawPie() 
{
	// TODO: Add your command handler code here

	DrawChart(2,"饼状图",50,400,13,"月份","数量");
}
void CMyDrawView::DrawChart(int type,CString title,int interval,int max,int sum,CString XN,CString YN)
{
	MyGraph = new CGraph(type);
	MyGraph->SetGraphTitle(title);
	//	MyGraph.SetGraphType(1);
	MyGraph->SetTickSpace(interval);
	MyGraph->SetTickRange(max);

	MyGraph->SetXAxisAlignment(50);
	MyGraph->SetXAxisLabel(XN);//可由外部传入
	MyGraph->SetYAxisLabel(YN);//可以由外部传入

	//set up some series
	for(int j=1;j<=sum;j++)
	{
		CGraphSeries* j = new CGraphSeries();
	/*CGraphSeries* series2 = new CGraphSeries();
	CGraphSeries* series3 = new CGraphSeries();*/
		j->SetLabel("day ");

/*	series2->SetLabel("day 2");
	series3->SetLabel("day 3");*/
		for(int i=0;i<sum;i++)
		{
			j->SetData(i, rand() % max);


/*	series1->SetData(1, 202);
	series1->SetData(2, 230);

	series2->SetData(i, 199);

	series2->SetData(1, 140);
	series2->SetData(2, 279);

	series3->SetData(i, 204);

/*	series3->SetData(1, 221);
	series3->SetData(2, 208);*/
		}
	MyGraph->AddSeries(j);
/*	MyGraph->AddSeries(series2);
	MyGraph->AddSeries(series3);*/
	}
	MyGraph->SetLegend(0, "game 1");

	MyGraph->SetLegend(1, "game 2");
	MyGraph->SetLegend(2, "game 3");

	//set up legend
		
	graphComplete = TRUE;
	Invalidate(TRUE);
}