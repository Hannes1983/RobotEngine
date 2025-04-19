#pragma once
#include "BaseReader.h"

class InputReader : public BaseReader
{  
public:
	InputReader(serial::Serial* _comPortP);
	~InputReader();
	void ReadFromNode(int _pinInd, INPUTERROR* _error);

};

