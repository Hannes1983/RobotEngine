#pragma once
#include "../third-party/include/serial/serial.h"
#include "Constants.hpp"
#include <wx/wx.h>


class InputReader
{  
public:
	InputReader(serial::Serial* _comPortP);
	~InputReader();
	bool ReadFromNode(int _inputIndex, INPUTERROR* _error);

private:
	serial::Serial* mArduinoComPortP = NULL;
	bool mReadActive;
};

