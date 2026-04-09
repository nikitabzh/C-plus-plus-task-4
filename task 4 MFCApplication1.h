
// task 4 MFCApplication1.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// Ctask4MFCApplication1App:
// Сведения о реализации этого класса: task 4 MFCApplication1.cpp
//

class Ctask4MFCApplication1App : public CWinApp
{
public:
	Ctask4MFCApplication1App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern Ctask4MFCApplication1App theApp;
