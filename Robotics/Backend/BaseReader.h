#pragma once
#include "../third-party/include/serial/serial.h"
#include "Constants.hpp"
#include <list>
#include <wx/wx.h>
#include <map>


class BaseReader {
public:
	BaseReader(serial::Serial* _comPortP = NULL);
	~BaseReader();
	virtual bool WriteToNode(PinState _request, OUTPUTERROR* _error) { return false; };
	virtual void ReadFromNode(int _pinInd, INPUTERROR* _error) {};
	std::map<int,PinState>* GetPinstates() { return mPinStatesP; }
	virtual void UpdatePinStates() {};

protected:

	virtual bool GetPinState(int _pinInd, OUTPUTERROR* _error) { return false; };
	serial::Serial* mArduinoComPortP = NULL;
	std::map<int,PinState>* mPinStatesP = NULL;
};

