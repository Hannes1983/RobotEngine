#include "RobotEngine.hpp"


RobotEngine::RobotEngine(std::string _port, const int _baudRate) {
	try {
		mArduinoComPortP = new serial::Serial(_port);
		mComPortIsUp = true;
		mArduinoComPortP->flushOutput();
	}
	catch (...) {
		wxLogError("RE::Constructor: Port could not be opened!");
		delete mArduinoComPortP;
		mArduinoComPortP = NULL;
		mComPortIsUp = false;
	}
	if (mArduinoComPortP != NULL && mArduinoComPortP->isOpen() ) {
		wxLogMessage("RE::Constructor: Port open succesfully!");
	}
	else {
		wxLogError("RE::Constructor: Port could not be opened!");
	}
	mDigitalIn2Active = false;


}

RobotEngine::~RobotEngine() {
	mArduinoComPortP->close();
	delete mArduinoComPortP;

}

void RobotEngine::Update() {
	mArduinoComPortP->flushInput();
	std::string input = "", repsonse = "NK";
	if (mDigitalIn2Active) {
		int count = 0;
		input = "dig2On\n";
		while (count < 10 && repsonse != "OK") {
			size_t bytes_wrote = mArduinoComPortP->write(input);
			repsonse = mArduinoComPortP->read(2);
			wxLogMessage("RE, It %d, bytes written %d", count, bytes_wrote);
			wxLogMessage("RE: Reponse %s", repsonse);

			count += 1;
		}
		if (count > 9 && repsonse != "OK") {
			wxLogError("RE: digital write timeout");
		}
		mArduinoComPortP->flush();
	}
	else {
		int count = 0;
		input = "dig2Off\n";
		while (count < 10 && repsonse != "OK") {
			size_t bytes_wrote = mArduinoComPortP->write(input);
			repsonse = mArduinoComPortP->read(2);
			wxLogMessage("RE, It %d, bytes written %d", count, bytes_wrote);
			wxLogMessage("RE: Reponse %s", repsonse);
			count += 1;
		}
		if (count > 9 && repsonse != "OK") {
			wxLogError("RE: digital write timeout");
		}
		mArduinoComPortP->flush();
	}
}