#include <wx/wxprec.h>
#include <wx/app.h> 
#include <wx/dynlib.h>
#include <wx/thread.h>
#include <wx/msw/wrapwin.h>
#include <process.h>

#include "guirunner.h"
#include "settingsdialog.h"

static const int CMD_SHOW_WINDOW = wxNewId();
static const int CMD_TERMINATE = wxNewId();
HWND gParent;
std::string gIniPath;
int gLastModalResult;

class MyDllApp : public wxApp
{
public:
    MyDllApp()
	{
		SetExitOnFrameDelete(false);
		Connect(CMD_SHOW_WINDOW, wxEVT_THREAD, wxThreadEventHandler(MyDllApp::OnShowWindow));
		Connect(CMD_TERMINATE, wxEVT_THREAD, wxThreadEventHandler(MyDllApp::OnTerminate));
	}

private:
    void OnShowWindow(wxThreadEvent&)
	{
		wxWindow win;
		win.SetHWND((WXHWND)gParent);
		SetTopWindow(&win);
		win.Enable(false);
		{
			SettingsDialog dlg(&win, gIniPath);
			gLastModalResult = dlg.ShowModal();
		}
		win.Enable(true);
	}
	
	void OnTerminate(wxThreadEvent&)
	{
		ExitMainLoop();
	}
};

wxIMPLEMENT_APP_NO_MAIN(MyDllApp);

namespace
{
	wxCriticalSection gs_wxStartupCS;
	HANDLE gs_wxMainThread = NULL;

	unsigned wxSTDCALL MyAppLauncher(void* event)
	{
	    const HINSTANCE hInstance = wxDynamicLibrary::MSWGetModuleHandle("audioconverter", &gs_wxMainThread);
	    if (!hInstance)
	        return 0; 
	    
		wxDISABLE_DEBUG_SUPPORT();

	    wxInitializer wxinit;
	    if (!wxinit.IsOk())
	        return 0; 
	    
		HANDLE hEvent = *(static_cast<HANDLE*>(event));
	    if (!SetEvent(hEvent))
	        return 0;

	    wxEntry(hInstance);
	    return 1;
	}
}

extern "C"
{
	void run_wx_gui_from_dll(const char* iniPath, HWND Parent)
	{
		gParent = Parent;
		gIniPath = iniPath;

	    wxCriticalSectionLocker lock(gs_wxStartupCS);

	    if (!gs_wxMainThread)
	    {
	        HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	        if (!hEvent)
	            return;

	        gs_wxMainThread = (HANDLE)_beginthreadex(NULL, 0, &MyAppLauncher, &hEvent, 0, NULL);

	        if (!gs_wxMainThread)
	        {
	            CloseHandle(hEvent);
	            return; 
	        }

	        WaitForSingleObject(hEvent, INFINITE);
	        CloseHandle(hEvent);
	    }

	    wxThreadEvent *event = new wxThreadEvent(wxEVT_THREAD, CMD_SHOW_WINDOW);
	    event->SetString("");
	    wxQueueEvent(wxApp::GetInstance(), event);
	}

	void wx_dll_cleanup()
	{
	    wxCriticalSectionLocker lock(gs_wxStartupCS);

	    if (!gs_wxMainThread)
	        return;
	    
		wxThreadEvent *event = new wxThreadEvent(wxEVT_THREAD, CMD_TERMINATE);
	    wxQueueEvent(wxApp::GetInstance(), event);
	    WaitForSingleObject(gs_wxMainThread, INFINITE);
	    CloseHandle(gs_wxMainThread);
	    gs_wxMainThread = NULL;
	}
}
