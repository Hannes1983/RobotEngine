#include "MainFrame.h"

IMPLEMENT_CLASS(MainFrame, wxWindow)


MainFrame::MainFrame(const wxString& title, const wxString& port) : wxFrame(nullptr, wxID_ANY, title) {
	
	//Logging
	mLogger = new wxLogWindow(this, "Trace", true, false);
	mRobotEngineP = new RobotEngine(port.ToStdString());
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

	mInputStatesP = mRobotEngineP->GetOutputPinStates();
	mOutputStatesP = mRobotEngineP->GetOutputPinStates();
	mDigital1Toggle = new wxToggleButton(mAnalogPanel, wxID_ANY, "Dig1: OFF", wxPoint(50, 50), wxSize(150, 35));
	mDigital1Toggle->Bind(wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, &MainFrame::OnDigitalButtonToggle, this, wxID_ANY, wxID_ANY, new ButtonArg(1));
	mDigital2Toggle = new wxToggleButton(mAnalogPanel, wxID_ANY, "Dig2: OFF", wxPoint(250, 50), wxSize(150, 35));
	mDigital2Toggle->Bind(wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, &MainFrame::OnDigitalButtonToggle, this, wxID_ANY, wxID_ANY, new ButtonArg(2));
	mDigital3Toggle = new wxToggleButton(mAnalogPanel, wxID_ANY, "Dig3: OFF", wxPoint(450, 50), wxSize(150, 35));
	mDigital3Toggle->Bind(wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, &MainFrame::OnDigitalButtonToggle, this, wxID_ANY, wxID_ANY, new ButtonArg(3));
	mDigital4Toggle = new wxToggleButton(mAnalogPanel, wxID_ANY, "Dig4: OFF", wxPoint(650, 50), wxSize(150, 35));
	mDigital4Toggle->Bind(wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, &MainFrame::OnDigitalButtonToggle, this, wxID_ANY, wxID_ANY, new ButtonArg(4));
	
	mDigital1Toggle->SetBackgroundColour((*mOutputStatesP)[1].isOn ? wxColour(*wxGREEN) : wxColour(*wxRED));
	mDigital2Toggle->SetBackgroundColour((*mOutputStatesP)[2].isOn ? wxColour(*wxGREEN) : wxColour(*wxRED));
	mDigital3Toggle->SetBackgroundColour((*mOutputStatesP)[3].isOn ? wxColour(*wxGREEN) : wxColour(*wxRED));
	mDigital4Toggle->SetBackgroundColour((*mOutputStatesP)[4].isOn ? wxColour(*wxGREEN) : wxColour(*wxRED));

	mDigital1Toggle->SetLabelText((*mOutputStatesP)[1].isOn ? "Dig1: ON" : "Dig1: OFF");
	mDigital2Toggle->SetLabelText((*mOutputStatesP)[2].isOn ? "Dig1: ON" : "Dig1: OFF");
	mDigital3Toggle->SetLabelText((*mOutputStatesP)[3].isOn ? "Dig1: ON" : "Dig1: OFF");
	mDigital4Toggle->SetLabelText((*mOutputStatesP)[4].isOn ? "Dig1: ON" : "Dig1: OFF");

	mDigital1Toggle->SetValue((*mOutputStatesP)[1].isOn);
	mDigital2Toggle->SetValue((*mOutputStatesP)[2].isOn);
	mDigital3Toggle->SetValue((*mOutputStatesP)[3].isOn);
	mDigital4Toggle->SetValue((*mOutputStatesP)[4].isOn);


	

	
}

MainFrame::~MainFrame() {
	
}

void MainFrame::OnDigitalButtonToggle(wxCommandEvent& event) {
	//Get userData
	ButtonArg* data = static_cast<ButtonArg*>(event.GetEventUserData());
	PinState request;
	switch (data->buttonNumber) {
		case 1:
			request.index = 1;
			request.isOn = mDigital1Toggle->GetValue();
			if (mDigital1Toggle->GetValue()) {
				mDigital1Toggle->SetLabelText("Dig1: ON");
				mDigital1Toggle->SetBackgroundColour(wxColour(*wxGREEN));
			}
			else {
				mDigital1Toggle->SetLabelText("Dig1: OFF");
				mDigital1Toggle->SetBackgroundColour(wxColour(*wxRED));
			}
			break;
		case 2:
			request.index = 2;
			request.isOn = mDigital2Toggle->GetValue();
			if (mDigital2Toggle->GetValue()) {
				mDigital2Toggle->SetLabelText("Dig2: ON");
				mDigital2Toggle->SetBackgroundColour(wxColour(*wxGREEN));
			}
			else {
				mDigital2Toggle->SetLabelText("Dig2: OFF");
				mDigital2Toggle->SetBackgroundColour(wxColour(*wxRED));
			}
			break;
		case 3:
			request.index = 3;
			request.isOn = mDigital3Toggle->GetValue();
			if (mDigital3Toggle->GetValue()) {
				mDigital3Toggle->SetLabelText("Dig3: ON");
				mDigital3Toggle->SetBackgroundColour(wxColour(*wxGREEN));
			}
			else {
				mDigital3Toggle->SetLabelText("Dig3: OFF");
				mDigital3Toggle->SetBackgroundColour(wxColour(*wxRED));
			}
			break;
		case 4:
			request.index = 4;
			request.isOn = mDigital4Toggle->GetValue();
			if (mDigital4Toggle->GetValue()) {
				mDigital4Toggle->SetLabelText("Dig4: ON");
				mDigital4Toggle->SetBackgroundColour(wxColour(*wxGREEN));
			}
			else {
				mDigital4Toggle->SetLabelText("Dig4: OFF");
				mDigital4Toggle->SetBackgroundColour(wxColour(*wxRED));
			}
			break;
		default:
			wxLogMessage("DigBtn request index %d out of range", data->buttonNumber);
			return;
			break;

	}
	mRobotEngineP->SetWriteRequest(request);
	
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
