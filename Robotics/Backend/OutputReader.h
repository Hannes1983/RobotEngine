#pragma once
#include "../third-party/include/serial/serial.h"
#include "Constants.hpp"
#include <list>
#include <wx/wx.h>



class OutputReader
{
public:
	OutputReader(serial::Serial* _comPortP);
	~OutputReader();
	bool WriteToNode(PinState _request, OUTPUTERROR* _error);

private:
	serial::Serial* mArduinoComPortP = NULL;
	std::list<PinState> mPinStates;
};

