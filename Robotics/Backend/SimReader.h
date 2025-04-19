#pragma once
#include "BaseReader.h"


class SimReader : public BaseReader
{
public:
	SimReader();
	~SimReader();
	bool WriteToNode(PinState _request, OUTPUTERROR* _error);
	void ReadFromNode(int _pinInd, INPUTERROR* _error);
};

