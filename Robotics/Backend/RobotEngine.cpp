#include "RobotEngine.hpp"
#include <chrono>

using namespace std::chrono_literals;


RobotEngine::RobotEngine(std::string _port, const int _baudRate) {
	mSimulated = (_port == "Sim");


	if (mSimulated) {
		mInputReaderP = new SimReader();
		mOutputReaderP = new SimReader();
	}
	else {
		try {
			mArduinoComPortP = new serial::Serial(_port);
			mInputReaderP = new InputReader(mArduinoComPortP);

			mOutputReaderP = new OutputReader(mArduinoComPortP);

			mComPortIsUp = true;
			mArduinoComPortP->flush();
		}
		catch (...) {
			wxLogError("RE::Constructor: Port %s could not be opened!", _port);
			delete mArduinoComPortP;
			mArduinoComPortP = NULL;
			mComPortIsUp = false;
		}
		if (mArduinoComPortP != NULL && mArduinoComPortP->isOpen()) {
			wxLogMessage("RE::Constructor: Port %s open succesfully!", _port);
			Sleep(6000); //ToDo: find better way to decide when port is ready
			mOutputReaderP->UpdatePinStates();

		}
		else {
			wxLogError("RE::Constructor: Port could not be opened!");
		}
	}
	
	
	mIOThreadP = new std::thread(&RobotEngine::UpdateFromController, this);
}

RobotEngine::~RobotEngine() {
	mArduinoComPortP->close();
	delete mArduinoComPortP;
	delete mInputReaderP;

}

void RobotEngine::HandleRequest() {

	if (mComPortIsUp && mWriteCurrRequest.pending) {
		mCommMutex.lock();
		OUTPUTERROR err;
		if (mOutputReaderP->WriteToNode(mWriteCurrRequest, &err)) {
		}
		else {
			wxLogMessage("RE: Request failed, err code %d", static_cast<int>(err));
		}
		mWriteCurrRequest.pending = false;
		mCommMutex.unlock();
	}
		
	
		
}


void RobotEngine::HandleInputs() {
	
	if (mComPortIsUp && mReadCurrRequest.pending) {
		mCommMutex.lock();
		
		INPUTERROR err;
		std::this_thread::sleep_for(10ms);
		mInputReaderP->ReadFromNode(mReadCurrRequest.index, &err);
		if (err != INPUTERROR::NO_IN_ERROR) {
			wxLogError("RE: Error rading node %d, error %d", mReadCurrRequest.index, static_cast<int>(err));
		}
		
		mReadCurrRequest.pending = false;
		mCommMutex.unlock();
		
	                                                       
	}
}

void RobotEngine::UpdateFromController() {
	mWriteCurrRequest.pending = false;
	mReadCurrRequest.pending = false;
	wxLogMessage("RE: Update thread started");
	while (true) {
		HandleRequest();
		HandleInputs();
		std::this_thread::sleep_for(100ms);
	}

}