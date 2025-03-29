#include "OutputReader.h"


OutputReader::OutputReader(serial::Serial* _comPortP) {
	mArduinoComPortP = _comPortP;
	for (int pin = MIN_OUTPUT_INDEX; pin < MAX_OUTPUT_INDEX; pin++) {
		mPinStates.push_back(PinState(pin, false));
	}
}
OutputReader::~OutputReader() {
	mArduinoComPortP = NULL;
}

bool OutputReader::WriteToNode(PinState _request, OUTPUTERROR* _error) {
	
	mArduinoComPortP->flushInput();
	if (_request.index < MIN_OUTPUT_INDEX || _request.index > MAX_OUTPUT_INDEX) {
		*_error = OUTPUTERROR::OUTPUT_IND_OOR;
		return false;
	}
	std::string input = std::to_string(_request.index) + "1";
	input += _request.isOn ? "1\n" : "0\n";
	wxLogMessage("OPR: Parsing request %s", input);
	std::string repsonse = "00000000";
	int count = 0;
	while (count < 10 && repsonse[6] != '1') {
		size_t bytes_wrote = mArduinoComPortP->write(input);
		repsonse = mArduinoComPortP->read(8);
		wxLogMessage("RE, It %d, bytes written %d", count, bytes_wrote);
		wxLogMessage("RE: Response %s", repsonse);
		count += 1;
	}
	if (count > 9 && repsonse[6] != '1') {
		wxLogMessage("OPR: Write timeout, error %s", repsonse);
		*_error = OUTPUTERROR::WRITE_TIME_OUT;
		return false;
	}
	*_error = OUTPUTERROR::NO_OUT_ERROR;
	mArduinoComPortP->flush();
	return true;
}

void OutputReader::ReadPinStates() {
	mArduinoComPortP->flushInput();

}