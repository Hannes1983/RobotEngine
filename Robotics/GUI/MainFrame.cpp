#include "MainFrame.h"
#include <chrono>

using namespace std::chrono_literals;

IMPLEMENT_CLASS(MainFrame, wxWindow)


MainFrame::MainFrame(const wxString& title, const wxString& port) : wxFrame(nullptr, wxID_ANY, title) {
	
	//Logging
	mLogger = new wxLogWindow(this, "Trace", true, false);
	mRobotEngineP = new RobotEngine(port.ToStdString());
	wxLog::SetLogLevel(wxLOG_Max);
	wxLog::SetActiveTarget(mLogger);
	wxLogMessage("Debugger active!");


	//Buttons and graphic panel
	wxPanel* mainPanel = new wxPanel(this);
	wxBoxSizer* inputBoxSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* outputBoxSizer = new wxBoxSizer(wxHORIZONTAL);
	mIOPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(1600, 210), wxTAB_TRAVERSAL, _T("ID_BUTTON"));
	mGraphicsPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 210), wxSize(1600, 1500));
	mIOPanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWFRAME));
	mQuitButton = new wxButton(mIOPanel, wxID_ANY, "Exit", wxPoint(1500, 50), wxSize(50, 35));
	mQuitButton->Bind(wxEVT_BUTTON, &MainFrame::OnQuitButtonClick, this);
	for (int ind = MIN_OUTPUT_INDEX; ind <= MAX_OUTPUT_INDEX; ind++) {
		wxString btnTxt = "Out" + wxString::Format(wxT("%i"), ind);
		int xpos = ind == 2 || ind == 3 ? 50 : 175;
		int ypos = ind == 2 || ind == 4 ? 50 : 100;
		mOutputButtons[ind] = new wxToggleButton(mIOPanel, wxID_ANY,btnTxt, wxPoint(xpos, ypos), wxSize(100, 35));
		mOutputButtons[ind]->Bind(wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, &MainFrame::OnDigitalButtonToggle, this, wxID_ANY, wxID_ANY, new ButtonArg(ind));
	}
	for (int ind = MIN_INPUT_INDEX; ind <= MAX_INPUT_INDEX; ind++) {
		wxString btnTxt = "In" + wxString::Format(wxT("%i"), ind);
		int xpos = ind == 6 || ind == 7 ? 360 : 485;
		int ypos = ind == 6 || ind == 8 ? 50 : 100;
		mInputButtons[ind] = new wxButton(mIOPanel, wxID_ANY, btnTxt, wxPoint(xpos, ypos), wxSize(100, 35));
		mInputButtons[ind]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::OnInputButtonClick, this, wxID_ANY, wxID_ANY, new ButtonArg(ind));
	}
	wxLogMessage("Buttons created.");

	//Get pointers to pin states
	mInputStatesP = mRobotEngineP->GetInputPinStates();
	mOutputStatesP = mRobotEngineP->GetOutputPinStates();
	wxLogMessage("IO states created.");

	mMonitorThreadP = new std::thread(&MainFrame::Update, this);

	

	
}

MainFrame::~MainFrame() {
	
}

void MainFrame::OnDigitalButtonToggle(wxCommandEvent& event) {
	//Get userData
	ButtonArg* data = static_cast<ButtonArg*>(event.GetEventUserData());
	PinState request(data->buttonNumber, !(*mOutputStatesP)[data->buttonNumber].isOn);

	mRobotEngineP->SetWriteRequest(request);
	
}

void MainFrame::OnInputButtonClick(wxCommandEvent& event) {
	//Get userData
	ButtonArg* data = static_cast<ButtonArg*>(event.GetEventUserData());
	PinState request(data->buttonNumber);
	mRobotEngineP->SetReadRequest(request);
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

void MainFrame::Update() {
	wxLogMessage("RE: Monitor thread started");
	while (true) {
		for (int ind = MIN_OUTPUT_INDEX; ind <= MAX_OUTPUT_INDEX; ind++) {
			bool isOn = (*mOutputStatesP)[ind].isOn;
			mOutputButtons[ind]->SetBackgroundColour(isOn ? wxColour(*wxGREEN) : wxColour(*wxRED));
		}
		for (int ind = MIN_INPUT_INDEX; ind <= MAX_INPUT_INDEX; ind++) {
			bool isOn = (*mInputStatesP)[ind].isOn;
			mInputButtons[ind]->SetBackgroundColour(isOn ? wxColour(*wxGREEN) : wxColour(*wxRED));
		}
		std::this_thread::sleep_for(100ms);
	}
}
