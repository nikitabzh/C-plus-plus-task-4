// task 4 MFCApplication1Dlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "task 4 MFCApplication1.h"
#include "task 4 MFCApplication1Dlg.h"
#include "afxdialogex.h"

#include "GraphProcessor.h"
#include <afxdlgs.h>
#include <string>
#include <stdexcept>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно Ctask4MFCApplication1Dlg

Ctask4MFCApplication1Dlg::Ctask4MFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TASK_4_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ctask4MFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Ctask4MFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_PROCESS, &Ctask4MFCApplication1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BTN_LOAD, &Ctask4MFCApplication1Dlg::OnBnClickedBtnLoad)
END_MESSAGE_MAP()


// Обработчики сообщений Ctask4MFCApplication1Dlg

BOOL Ctask4MFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void Ctask4MFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void Ctask4MFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR Ctask4MFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);

}

// Кнопка поиска компонент связности и сохранения результата
void Ctask4MFCApplication1Dlg::OnBnClickedButton1()
{
	// Вызов стандартного диалога "Сохранить файл"
	CFileDialog fileDlg(FALSE, _T("txt"), _T("result.txt"), OFN_OVERWRITEPROMPT, _T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||"));

	if (fileDlg.DoModal() == IDOK)
	{
		// Конвертация MFC пути в стандартную строку STL
		CT2CA pszConvertedAnsiString(fileDlg.GetPathName());
		std::string path(pszConvertedAnsiString);

		try {
			// Вызов логики обработки из ядра
			m_graph.process(path);
			MessageBox(_T("Компоненты связности найдены и успешно сохранены!"), _T("Успех"), MB_ICONINFORMATION);
		}
		catch (const std::exception& e) {
			// Обработка исключений и логирование ошибок
			LOG_ERR(e.what());
			MessageBox(CString(e.what()), _T("Ошибка вычислений"), MB_ICONERROR);
		}
	}
}

// Кнопка загрузки графа из файла
void Ctask4MFCApplication1Dlg::OnBnClickedBtnLoad()
{
	// Вызов стандартного диалога "Открыть файл"
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		_T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||"));

	if (fileDlg.DoModal() == IDOK)
	{
		// Конвертация MFC пути в стандартную строку STL
		CT2CA pszConvertedAnsiString(fileDlg.GetPathName());
		std::string path(pszConvertedAnsiString);

		try {
			// Вызов логики загрузки из ядра
			m_graph.loadFromFile(path);
			MessageBox(_T("Граф успешно загружен в память!"), _T("Успех"), MB_ICONINFORMATION);
		}
		catch (const std::exception& e) {
			LOG_ERR(e.what());
			MessageBox(CString(e.what()), _T("Ошибка загрузки"), MB_ICONERROR);
		}
	}
}