#pragma once
#include <wx/wx.h>
#include "../third-party/include/serial/serial.h"



class RobotEngine
{
public:
	RobotEngine(const std::string _port, const int _baudRate = 9600);
	~RobotEngine();

	void Update();
	void SetDigital(const bool _isSet) { mDigitalIn2Active = _isSet; }
	bool PortIsUp() { return mComPortIsUp; }
private:
	serial::Serial* mArduinoComPortP = NULL;
	bool mDigitalIn2Active;
	bool mComPortIsUp;



};

