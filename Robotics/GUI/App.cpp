#include "App.h"

wxIMPLEMENT_APP(App);


bool App::OnInit() {

	//Read arguments
	//Read arguments
	int arg = 0;
	wxString port = "COM3";
	while (arg < wxApp::argc) {
		wxString arg_str = wxApp::argv[arg];
		if (arg_str == "-port") {
			arg++;
			port = wxApp::argv[arg];
		}
		arg++;
	}


	wxFrame* mainFrame = new MainFrame("Robot Engine",port);



	//Start application
	mainFrame->SetClientSize(1600, 1600);
	mainFrame->Center();
	//mainFrame->CreateStatusBar();
	mainFrame->Show();

	//Quit event
	this->Bind(wxEVT_MENU, [mainFrame](wxCommandEvent&)->void {
		mainFrame->Destroy();
		/* 1. method wxWindow::Close
		 * 2. event type wxEVT_CLOSE_WINDOW
		 * 3. method wxTopLevelWindow::OnCloseWindow
		 * 4. method wxTopLevelWindow::Destroy (overriding wxWindow::Destroy)
		 * 5. op delete
		 */
		}, wxID_EXIT);
	return true;
}

int App::OnExit() {
	wxMessageBox("Quitting Robot GUI", wxEmptyString, wxOK | wxICON_INFORMATION);
	return this->wxApp::OnExit();
}

