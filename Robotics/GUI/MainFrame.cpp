#include "MainFrame.h"

IMPLEMENT_CLASS(MainFrame, wxWindow)


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	
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
	mDigital2Toggle = new wxToggleButton(mAnalogPanel, wxID_ANY, "Dig2: OFF", wxPoint(50, 50), wxSize(150, 35));
	mDigital2Toggle->Bind(wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, &MainFrame::OnDigitalButtonToggle, this);
	


	mRobotEngineP = new RobotEngine("COM3");
	//mUpdateThreadP = new std::thread(&MainFrame::Update, this);

	
}

MainFrame::~MainFrame() {
	
}

void MainFrame::OnDigitalButtonToggle(wxCommandEvent& event) {
	mRobotEngineP->SetDigital(mDigital2Toggle->GetValue());
	if (mDigital2Toggle->GetValue()) {
		mDigital2Toggle->SetLabelText("Dig2: ON");
	}
	else {
		mDigital2Toggle->SetLabelText("Dig2: OFF");
	}
	mRobotEngineP->Update();
}

void MainFrame::Update() {

	while (true) {
		if (!mRobotEngineP->PortIsUp()) {
			continue;
		}
		try {
			mRobotEngineP->Update();
		}
		catch (...) {
			wxLogError("MainFrame: Caught exception during update");
		}
	}
}