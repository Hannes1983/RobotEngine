#pragma once
#include "InputReader.h"
#include "OutputReader.h"
#include <thread>
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
	const std::map<int,PinState> GetOutputPinStates() const { return mOutputReaderP->GetPinstates(); }
	bool PortIsUp() { return mComPortIsUp; }
private:

	void HandleRequest();
	void HandleInputs();

	void CopyInputPinStates() { mCurrInputStates = mInputReaderP->GetPinstates(); }

	serial::Serial* mArduinoComPortP = NULL;
	InputReader* mInputReaderP = NULL;
	OutputReader* mOutputReaderP = NULL;
	bool mDigitalIn2Active;
	bool mComPortIsUp;
	PinState mWriteCurrRequest;
	std::map<int, PinState> mCurrInputStates;

	std::thread* mWriteThreadP;
	std::thread* mReadThreadP;
	std::mutex mCommMutex;



};

