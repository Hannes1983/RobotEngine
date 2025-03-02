#include "App.h"

wxIMPLEMENT_APP(App);


bool App::OnInit() {

	//Read arguments
	//serial::Serial ard_serial_port("COM3", 19200);
	return true;
}

int App::OnExit() {
	//wxMessageBox("Quitting Physics Engine", wxEmptyString, wxOK | wxICON_INFORMATION);
	return this->wxApp::OnExit();
}

