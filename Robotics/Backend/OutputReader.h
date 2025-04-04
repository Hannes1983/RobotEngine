#pragma once
#include "../third-party/include/serial/serial.h"
#include "Constants.hpp"
#include <list>
#include <wx/wx.h>
#include <map>


class OutputReader
{
public:
	OutputReader(serial::Serial* _comPortP);
	~OutputReader();
	bool WriteToNode(PinState _request, OUTPUTERROR* _error);
	const std::map<int,PinState> GetPinstates() const { return mPinStates; }
	void UpdatePinStates();

private:

	bool GetPinState(int _pinInd, OUTPUTERROR* _error);
	serial::Serial* mArduinoComPortP = NULL;
	std::map<int,PinState> mPinStates;
};

