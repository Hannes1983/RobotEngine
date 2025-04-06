#pragma once
#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <wx/tglbtn.h>
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
	void OnQuitButtonClick(wxCommandEvent& event);

	wxPanel* mAnalogPanel;
	wxPanel* mDigitalPanel;
	wxLog* mLogger;

	RobotEngine* mRobotEngineP = NULL;
	wxButton* mQuitButton;
	wxToggleButton* mDigital1Toggle;
	wxToggleButton* mDigital2Toggle;
	wxToggleButton* mDigital3Toggle;
	wxToggleButton* mDigital4Toggle;

	std::map<int, PinState>* mInputStatesP;
	std::map<int, PinState>* mOutputStatesP;

};

