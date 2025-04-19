#include "BaseReader.h"


BaseReader::BaseReader(serial::Serial* _comPortP) {
	mArduinoComPortP = _comPortP;
}
BaseReader::~BaseReader() {
	mArduinoComPortP = NULL;
	delete mPinStatesP;
}

