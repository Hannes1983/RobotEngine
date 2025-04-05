#include "RobotEngine.hpp"
#include <chrono>

using namespace std::chrono_literals;


RobotEngine::RobotEngine(std::string _port, const int _baudRate) {
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
	if (mArduinoComPortP != NULL && mArduinoComPortP->isOpen() ) {
		wxLogMessage("RE::Constructor: Port %s open succesfully!", _port);
		Sleep(6000); //ToDo: find better way to decide when port is ready
		mOutputReaderP->UpdatePinStates();
	
	}
	else {
		wxLogError("RE::Constructor: Port could not be opened!");
	}
	
	
	mWriteThreadP = new std::thread(&RobotEngine::HandleRequest, this);
	mReadThreadP = new std::thread(&RobotEngine::HandleInputs, this);

}

RobotEngine::~RobotEngine() {
	mArduinoComPortP->close();
	delete mArduinoComPortP;
	delete mInputReaderP;

}

void RobotEngine::HandleRequest() {
	wxLogMessage("RE: Update thread started");
	mWriteCurrRequest.pending = false;
	while (true) {
		
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
		
		std::this_thread::sleep_for(100ms);;
		
	}

}

void RobotEngine::HandleInputs() {
	wxLogMessage("RE: Read thread started");
	while (true) {
		if (mComPortIsUp) {
			mCommMutex.lock();
			bool stateUpdated = false;
			for (int pin = MIN_INPUT_INDEX; pin <= MAX_INPUT_INDEX; pin++) {
				INPUTERROR err;
				std::this_thread::sleep_for(10ms);
				bool currState = mInputReaderP->ReadFromNode(pin, &err);
				stateUpdated &= currState;
				if (err != INPUTERROR::NO_IN_ERROR) {
					wxLogError("RE: Error rading node %d, error %d", pin, static_cast<int>(err));
				}
				wxLogMessage("State %d: %d", pin, static_cast<int>(currState));
			}
			mCommMutex.unlock();
			if (stateUpdated) {
				wxLogMessage("RE: input state changed!");
				CopyInputPinStates();
			}
		std::this_thread::sleep_for(100ms);
		}
	}
}