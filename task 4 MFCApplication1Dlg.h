// task 4 MFCApplication1Dlg.h: файл заголовка
//

#pragma once
#include "GraphProcessor.h"

// Диалоговое окно Ctask4MFCApplication1Dlg
class Ctask4MFCApplication1Dlg : public CDialogEx
{
	// Создание
public:
	Ctask4MFCApplication1Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TASK_4_MFCAPPLICATION1_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


	// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtnLoad();

private:
	GraphProcessor m_graph;
};