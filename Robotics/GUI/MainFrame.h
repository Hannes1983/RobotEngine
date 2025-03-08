#pragma once
#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <wx/tglbtn.h>
#include <thread>
#include "../Backend/RobotEngine.hpp"


class MainFrame : public  wxFrame
{
public:
	MainFrame(const wxString& title);
	~MainFrame();

protected:
	DECLARE_CLASS(MainFrame)
private:
	void OnDigitalButtonToggle(wxCommandEvent& event);
	void OnQuitButtonClick(wxCommandEvent& event);

	void Update();
	wxPanel* mAnalogPanel;
	wxPanel* mDigitalPanel;
	wxLog* mLogger;

	RobotEngine* mRobotEngineP = NULL;
	wxButton* mQuitButton;
	wxToggleButton* mDigital2Toggle;
	std::thread* mUpdateThreadP;



};

