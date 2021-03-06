#pragma once
#include "TabDlg.h"
#include "CalendarHelper.h"
#include "DrawCommon.h"

// CHistoryTrafficCalendarDlg 对话框

class CHistoryTrafficCalendarDlg : public CTabDlg
{
	DECLARE_DYNAMIC(CHistoryTrafficCalendarDlg)

public:
	CHistoryTrafficCalendarDlg(deque<HistoryTraffic>& history_traffics, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CHistoryTrafficCalendarDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HISTORY_TRAFFIC_CALENDAR_DIALOG };
#endif

protected:
	deque<HistoryTraffic>& m_history_traffics;
	DayTraffic m_calendar[CALENDAR_HEIGHT][CALENDAR_WIDTH];
	int m_year;
	int m_month;

	void SetDayTraffic();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
