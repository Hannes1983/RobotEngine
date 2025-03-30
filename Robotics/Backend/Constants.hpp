#pragma once

enum OUTPUTERROR {
	NO_OUT_ERROR = 0,
	WRITE_TIME_OUT,
	OUTPUT_IND_OOR
};
enum INPUTERROR {
	NO_IN_ERROR = 0,
	READ_TIME_OUT,
	INPUT_IND_OOR
};

const int MIN_OUTPUT_INDEX = 1;
const int MAX_OUTPUT_INDEX = 4;
const int MIN_INPUT_INDEX = 5;
const int MAX_INPUT_INDEX = 8;

//Arduino comm. protocol
// Request XYZ: X = pin, Y = write(1) / read(0), Z = write state (High(1) / Low(0))
// Reponse: 1 byte as string bit 7: state (high/low) bit 6: process done, bit 5-0: error codes

struct PinState {
	PinState(int _index = -1, bool _isOn = false, bool _pending = true) {
		index = _index;
		isOn = _isOn;
		pending = _pending;

	}
	int index;
	bool isOn;
	bool pending;
};



