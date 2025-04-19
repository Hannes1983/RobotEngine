#pragma once
#include "BaseReader.h"


class OutputReader : public BaseReader
{
public:
	OutputReader(serial::Serial* _comPortP);
	~OutputReader();
	bool WriteToNode(PinState _request, OUTPUTERROR* _error);
	void UpdatePinStates();

private:

	bool GetPinState(int _pinInd, OUTPUTERROR* _error);
};

