#include "InputReader.h"

InputReader::InputReader(serial::Serial* _comPortP) {
	mArduinoComPortP = _comPortP;
}
InputReader::~InputReader() {
	mArduinoComPortP = NULL;
}

bool InputReader::ReadFromNode(int _inputIndex, INPUTERROR* _error) {
	mArduinoComPortP->flushInput();
	if (_inputIndex < MIN_INPUT_INDEX || _inputIndex > MAX_INPUT_INDEX) {
		*_error = INPUTERROR::INPUT_IND_OOR;
		return false;
	}
	std::string input = "read", repsonse = "NK";
	input.append(std::to_string(_inputIndex));
	int count = 0;
	while (count < 10 && (repsonse != "1" || repsonse != "0")) {
		size_t bytes_wrote = mArduinoComPortP->write(input);
		repsonse = mArduinoComPortP->read(1);
		wxLogMessage("RE, It %d, bytes written %d", count, bytes_wrote);
		wxLogMessage("RE: Reponse %s", repsonse);
		count += 1;
	}
	if (count > 9 && (repsonse != "1" || repsonse != "0")) {
		wxLogError("RE: digital read timeout");
		*_error = INPUTERROR::READ_TIME_OUT;
		mArduinoComPortP->flush();
		return false;
	}
	*_error = INPUTERROR::NO_IN_ERROR;
	return repsonse == "1" ? true : false;
	mArduinoComPortP->flush();

	

}
