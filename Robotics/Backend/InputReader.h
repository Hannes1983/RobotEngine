#pragma once
#include "../third-party/include/serial/serial.h"
#include "Constants.hpp"
#include <wx/wx.h>
#include <map>

class InputReader
{  
public:
	InputReader(serial::Serial* _comPortP);
	~InputReader();
	bool ReadFromNode(int _pinInd, INPUTERROR* _error);
	const std::map<int, PinState> GetPinstates() const { return mPinStates; }

private:
	serial::Serial* mArduinoComPortP = NULL;
	bool mReadActive;
	std::map<int, PinState> mPinStates;
};

