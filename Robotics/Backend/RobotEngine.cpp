#include "RobotEngine.hpp"


RobotEngine::RobotEngine(std::string _port, const int _baudRate) {
	try {
		mArduinoComPortP = new serial::Serial(_port);
		mInputReaderP = new InputReader(mArduinoComPortP);
		
		mOutputReaderP = new OutputReader(mArduinoComPortP);
		
		mComPortIsUp = true;
		mArduinoComPortP->flushOutput();
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
	
	
	mUpdateThreadP = new std::thread(&RobotEngine::Update, this);

}

RobotEngine::~RobotEngine() {
	mArduinoComPortP->close();
	delete mArduinoComPortP;
	delete mInputReaderP;

}

void RobotEngine::Update() {
	wxLogMessage("RE: Update thread started");
	mWriteCurrRequest.pending = false;
	while (true) {
		mRequestMutex.lock();

		if (mComPortIsUp && mWriteCurrRequest.pending) {
			OUTPUTERROR err;
			if (mOutputReaderP->WriteToNode(mWriteCurrRequest, &err)) {
			}
			else {
				wxLogMessage("RE: Request failed, err code %d", static_cast<int>(err));
			}
			mWriteCurrRequest.pending = false;
		}
		mRequestMutex.unlock();
		Sleep(10);
		
	}

}