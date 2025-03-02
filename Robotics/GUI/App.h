#pragma once
#include <wx/wx.h>
#include "../third-party/include/serial/serial.h"


class App : public wxApp
{
public:
	bool OnInit();
	int OnExit();

};

