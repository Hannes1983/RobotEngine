#pragma once
#include "InputReader.h"
#include "OutputReader.h"

# include "SimReader.h"
#include <mutex>

class RobotEngine
{
public:
	RobotEngine(const std::string _port, const int _baudRate = 9600);
	~RobotEngine();

	void SetWriteRequest(const PinState _request ) {
		mCommMutex.lock();
		mWriteCurrRequest = _request; 
		mCommMutex.unlock();
	}
	void SetReadRequest(const PinState _request) {
		mCommMutex.lock();
		mReadCurrRequest = _request;
		mCommMutex.unlock();
	}
	std::map<int,PinState>* GetOutputPinStates() { return mOutputReaderP->GetPinstates(); }
	std::map<int, PinState>* GetInputPinStates() { return mInputReaderP->GetPinstates(); }
	void UpdateFromController();

	bool PortIsUp() { return mComPortIsUp; }
private:
	void HandleRequest();
	void HandleInputs();

	serial::Serial* mArduinoComPortP = NULL;
	BaseReader* mInputReaderP = NULL;
	BaseReader* mOutputReaderP = NULL;
	bool mDigitalIn2Active;
	bool mComPortIsUp;
	PinState mWriteCurrRequest;
	PinState mReadCurrRequest;

	std::thread* mIOThreadP;
	std::mutex mCommMutex;

	bool mSimulated;



};

