#pragma once
#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <wx/tglbtn.h>
#include <thread>
#include "../Backend/RobotEngine.hpp"

// Struct for passing arguments in Bind()
struct ButtonArg : public wxObject {
	ButtonArg(int nbr = 0) { buttonNumber = nbr; }
	int buttonNumber;
};

class MainFrame : public  wxFrame
{
public:
	MainFrame(const wxString& title, const wxString& port = "");
	~MainFrame();

protected:
	DECLARE_CLASS(MainFrame)
private:
	void OnDigitalButtonToggle(wxCommandEvent& event);
	void OnInputButtonClick(wxCommandEvent& event);
	void OnQuitButtonClick(wxCommandEvent& event);
	void Update();

	wxPanel* mIOPanel;
	wxPanel* mGraphicsPanel;
	wxLog* mLogger;

	RobotEngine* mRobotEngineP = NULL;
	wxButton* mQuitButton;
	std::map<int, wxToggleButton*> mOutputButtons;
	std::map<int, wxButton*> mInputButtons;
	wxToggleButton* mDigital1Toggle;
	wxToggleButton* mDigital2Toggle;
	wxToggleButton* mDigital3Toggle;
	wxToggleButton* mDigital4Toggle;

	wxButton* mInputButton1;
	wxButton* mInputButton2;
	wxButton* mInputButton3;
	wxButton* mInputButton4;

	std::map<int, PinState>* mInputStatesP;
	std::map<int, PinState>* mOutputStatesP;

	std::thread* mMonitorThreadP;

};

