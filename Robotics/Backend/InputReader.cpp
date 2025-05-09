#include "InputReader.h"

InputReader::InputReader(serial::Serial* _comPortP) : BaseReader(_comPortP) {
	mPinStatesP = new std::map<int, PinState>;
	for (int ind = MIN_INPUT_INDEX; ind <= MAX_INPUT_INDEX; ind++) {
		(*mPinStatesP).insert({ ind, PinState(ind, false, false) });
	}
}
InputReader::~InputReader() {
	mArduinoComPortP = NULL;
	delete mPinStatesP;
}

void InputReader::ReadFromNode(int _pinInd, INPUTERROR* _error) {
	mArduinoComPortP->flushInput();
	if (_pinInd < MIN_INPUT_INDEX || _pinInd > MAX_INPUT_INDEX) {
		*_error = INPUTERROR::INPUT_IND_OOR;
		return;
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
		return;
	}
	*_error = INPUTERROR::NO_IN_ERROR;
	(*mPinStatesP)[_pinInd].isOn = repsonse[7] == '1' ? true : false;
	wxLogMessage("RE: handled read from pin %d, state %d", _pinInd, (*mPinStatesP)[_pinInd].isOn);
	mArduinoComPortP->flush();

	

}
