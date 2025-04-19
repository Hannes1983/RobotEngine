#include "SimReader.h"


SimReader::SimReader() {
	
	mPinStatesP = new std::map<int, PinState>;
	for (int ind = MIN_OUTPUT_INDEX; ind <= MAX_INPUT_INDEX; ind++) {
		(*mPinStatesP).insert({ ind, PinState(ind, false, false) });
	}
}
SimReader::~SimReader() {
	delete mPinStatesP;
}

bool SimReader::WriteToNode(PinState _request, OUTPUTERROR* _error) {
	if (_request.index < MIN_OUTPUT_INDEX || _request.index > MAX_OUTPUT_INDEX) {
		*_error = OUTPUTERROR::OUTPUT_IND_OOR;
		return false;
	}
	(*mPinStatesP)[_request.index].isOn = _request.isOn;
	return true;
}

void SimReader::ReadFromNode(int _pinInd, INPUTERROR* _error) {
	if (_pinInd < MIN_INPUT_INDEX || _pinInd > MAX_INPUT_INDEX) {
		*_error = INPUTERROR::INPUT_IND_OOR;
		return;
	}
	(*mPinStatesP)[_pinInd].isOn = !(*mPinStatesP)[_pinInd].isOn;
};
