// HistoryTrafficCalendarDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "TrafficMonitor.h"
#include "HistoryTrafficCalendarDlg.h"
#include "afxdialogex.h"


// CHistoryTrafficCalendarDlg 对话框

IMPLEMENT_DYNAMIC(CHistoryTrafficCalendarDlg, CTabDlg)

CHistoryTrafficCalendarDlg::CHistoryTrafficCalendarDlg(deque<HistoryTraffic>& history_traffics, CWnd* pParent /*=nullptr*/)
	: CTabDlg(IDD_HISTORY_TRAFFIC_CALENDAR_DIALOG, pParent), m_history_traffics(history_traffics)
{

}

CHistoryTrafficCalendarDlg::~CHistoryTrafficCalendarDlg()
{
}

void CHistoryTrafficCalendarDlg::SetDayTraffic()
{
	for (int i{}; i < CALENDAR_HEIGHT; i++)
	{
		for (int j{}; j < CALENDAR_WIDTH; j++)
		{
			HistoryTraffic history_traffic;
			history_traffic.year = m_year;
			history_traffic.month = m_month;
			history_traffic.day = m_calendar[i][j].day;
			//使用二分法查找日历中每一个日期的流量
			if (history_traffic.day > 0)
			{
				if (std::binary_search(m_history_traffics.begin(), m_history_traffics.end(), history_traffic, HistoryTraffic::DateGreater))
				{
					auto iter = std::lower_bound(m_history_traffics.begin(), m_history_traffics.end(), history_traffic, HistoryTraffic::DateGreater);
					if(iter != m_history_traffics.end())
						m_calendar[i][j].traffic = iter->kBytes;
				}
			}
		}
	}
}

void CHistoryTrafficCalendarDlg::DoDataExchange(CDataExchange* pDX)
{
	CTabDlg::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHistoryTrafficCalendarDlg, CTabDlg)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CHistoryTrafficCalendarDlg 消息处理程序


BOOL CHistoryTrafficCalendarDlg::OnInitDialog()
{
	CTabDlg::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_year = m_history_traffics[0].year;
	m_month = m_history_traffics[0].month;
	CCalendarHelper::GetCalendar(m_year, m_month, m_calendar);
	SetDayTraffic();


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CHistoryTrafficCalendarDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CTabDlg::OnPaint()
	int start_x = theApp.DPI(10);
	int start_y = start_x;
	int width = theApp.DPI(40);
	int height = theApp.DPI(30);
	CRect rect{};
	rect.left = start_x;
	rect.top = start_y;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;
	CDrawCommon draw;
	draw.Create(&dc, this);
	//画星期的行
	for (int i{}; i < CALENDAR_WIDTH; i++)
	{
		rect.MoveToX(start_x + i * width);
		
		if (i % 2 == 0)
			draw.SetBackColor(RGB(1, 84, 151));
		else
			draw.SetBackColor(RGB(1, 107, 191));
		CString str;
		switch (i)
		{
		case 0:
			str.LoadString(IDS_SUNDAY);
			break;
		case 1:
			str.LoadString(IDS_MONDAY);
			break;
		case 2:
			str.LoadString(IDS_TUESDAY);
			break;
		case 3:
			str.LoadString(IDS_WEDNESDAY);
			break;
		case 4:
			str.LoadString(IDS_THURSDAY);
			break;
		case 5:
			str.LoadString(IDS_FRIDAY);
			break;
		case 6:
			str.LoadString(IDS_SATURDAY);
			break;
		}
		draw.DrawWindowText(rect, str, RGB(255, 255, 255), Alignment::CENTER, true);
	}
}
