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
		mRequestMutex.lock();
		mWriteCurrRequest = _request; 
		mRequestMutex.unlock();
	}
	bool PortIsUp() { return mComPortIsUp; }
private:

	void Update();

	serial::Serial* mArduinoComPortP = NULL;
	InputReader* mInputReaderP = NULL;
	OutputReader* mOutputReaderP = NULL;
	bool mDigitalIn2Active;
	bool mComPortIsUp;
	PinState mWriteCurrRequest;

	std::thread* mUpdateThreadP;
	std::mutex mRequestMutex;



};

