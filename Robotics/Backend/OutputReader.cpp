#include "OutputReader.h"


OutputReader::OutputReader(serial::Serial* _comPortP) : BaseReader(_comPortP) {
	mPinStatesP = new std::map<int, PinState>;
	for (int ind = MIN_OUTPUT_INDEX; ind <= MAX_OUTPUT_INDEX; ind++) {
		(*mPinStatesP).insert({ ind, PinState(ind, false, false) });
	}
}
OutputReader::~OutputReader() {
	mArduinoComPortP = NULL;
	delete mPinStatesP;
}

bool OutputReader::WriteToNode(PinState _request, OUTPUTERROR* _error) {
	
	mArduinoComPortP->flushInput();
	if (_request.index < MIN_OUTPUT_INDEX || _request.index > MAX_OUTPUT_INDEX) {
		*_error = OUTPUTERROR::OUTPUT_IND_OOR;
		return false;
	}
	std::string input = std::to_string(_request.index) + "1";
	input += _request.isOn ? "1\n" : "0\n";
	std::string repsonse = "00000000";
	int count = 0;
	while (count < 10 && repsonse[6] != '1') {
		size_t bytes_wrote = mArduinoComPortP->write(input);
		repsonse = mArduinoComPortP->read(8);
		count += 1;
	}
	if (count > 9 && repsonse[6] != '1') {
		wxLogMessage("OPR: Write timeout, error %s", repsonse);
		*_error = OUTPUTERROR::WRITE_TIME_OUT;
		return false;
	}
	(*mPinStatesP)[_request.index].isOn = repsonse[7] == '1' ? true : false;
	*_error = OUTPUTERROR::NO_OUT_ERROR;
	mArduinoComPortP->flush();
	wxLogMessage("RE: handled write to pin %d, state %d", _request.index, (*mPinStatesP)[_request.index].isOn);
	return true;
}

bool OutputReader::GetPinState(int _pinInd, OUTPUTERROR* _error) {
	mArduinoComPortP->flushInput();
	std::string input = std::to_string(_pinInd) + "00\n";
	std::string repsonse = "00000000";
	int count = 0;
	while (count < 10 && repsonse[6] != '1') {
		size_t bytes_wrote = mArduinoComPortP->write(input);
		repsonse = mArduinoComPortP->read(8);
	
		count += 1;
	}
	if (count > 9 && repsonse[6] != '1') {
		wxLogMessage("OPR: Write timeout, error %s", repsonse);
		*_error = OUTPUTERROR::WRITE_TIME_OUT;
		return false;
	}
	*_error = OUTPUTERROR::NO_OUT_ERROR;
	mArduinoComPortP->flush();

	return repsonse[7] == '1' ? true : false;
	
}

void OutputReader::UpdatePinStates() {
	OUTPUTERROR dummy;
	for (int pin = MIN_OUTPUT_INDEX; pin <= MAX_OUTPUT_INDEX; pin++) {
		(*mPinStatesP).insert({ pin,PinState(pin, GetPinState(pin, &dummy)) });
	}
}