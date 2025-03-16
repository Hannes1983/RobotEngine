#include "MainFrame.h"

IMPLEMENT_CLASS(MainFrame, wxWindow)


MainFrame::MainFrame(const wxString& title, const wxString& port) : wxFrame(nullptr, wxID_ANY, title) {
	
	//Logging
	mLogger = new wxLogWindow(this, "Trace", true, false);
	wxLog::SetLogLevel(wxLOG_Max);
	wxLog::SetActiveTarget(mLogger);
	wxLogMessage("Debugger active!");

	wxPanel* mainPanel = new wxPanel(this);
	wxBoxSizer* inputBoxSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* outputBoxSizer = new wxBoxSizer(wxHORIZONTAL);
	mAnalogPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(1600, 100), wxTAB_TRAVERSAL, _T("ID_BUTTON"));
	mDigitalPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 100), wxSize(1600, 1500));
	mAnalogPanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWFRAME));
	mQuitButton = new wxButton(mAnalogPanel, wxID_ANY, "Exit", wxPoint(1500, 50), wxSize(50, 35));
	mQuitButton->Bind(wxEVT_BUTTON, &MainFrame::OnQuitButtonClick, this);

	mDigital2Toggle = new wxToggleButton(mAnalogPanel, wxID_ANY, "Dig2: OFF", wxPoint(50, 50), wxSize(150, 35));
	mDigital2Toggle->Bind(wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, &MainFrame::OnDigitalButtonToggle, this);
	


	mRobotEngineP = new RobotEngine(port.ToStdString());

	
}

MainFrame::~MainFrame() {
	
}

void MainFrame::OnDigitalButtonToggle(wxCommandEvent& event) {
	PinState request(2, mDigital2Toggle->GetValue());
	mRobotEngineP->SetWriteRequest(request);
	if (mDigital2Toggle->GetValue()) {
		mDigital2Toggle->SetLabelText("Dig2: ON");
	}
	else {
		mDigital2Toggle->SetLabelText("Dig2: OFF");
	}
}

void MainFrame::OnQuitButtonClick(wxCommandEvent& event) {
	wxString msg = "Are you sure?";
	if (wxMessageBox(msg, "Closing application", wxICON_QUESTION | wxYES_NO, this) == wxYES) {
		wxLogMessage("Closing application...");
		Sleep(1000);
		delete mRobotEngineP;
		this->Destroy();
	}
	else {
		return;
	}
}
