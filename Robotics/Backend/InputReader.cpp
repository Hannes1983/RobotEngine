#include "InputReader.h"

InputReader::InputReader(serial::Serial* _comPortP) {
	mArduinoComPortP = _comPortP;
}
InputReader::~InputReader() {
	mArduinoComPortP = NULL;
}

bool InputReader::ReadFromNode(int _pinInd, INPUTERROR* _error) {
	mArduinoComPortP->flushInput();
	if (_pinInd < MIN_INPUT_INDEX || _pinInd > MAX_INPUT_INDEX) {
		*_error = INPUTERROR::INPUT_IND_OOR;
		return false;
	}
	std::string input = std::to_string(_pinInd) + "00\n";
	std::string repsonse = "00000000";
	int count = 0;
	while (count < 10 && repsonse[6] != '1') {
		size_t bytes_wrote = mArduinoComPortP->write(input);
		repsonse = mArduinoComPortP->read(8);
		count += 1;
	}
	if (count > 9 && repsonse[6] != '1') {
		*_error = INPUTERROR::READ_TIME_OUT;
		return false;
	}
	*_error = INPUTERROR::NO_IN_ERROR;
	bool oldState = mPinStates[_pinInd].isOn;
	mPinStates[_pinInd].isOn = repsonse[7] != '1' ? true : false;
	mArduinoComPortP->flush();
	return oldState != mPinStates[_pinInd].isOn;

	

}
