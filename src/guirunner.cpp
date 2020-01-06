#include <wx/wxprec.h>
#include <wx/app.h> 
#include <wx/dynlib.h>
#include <wx/msw/wrapwin.h>
#include <process.h>

#include "guirunner.h"
#include "settingsdialog.h"

namespace
{
	HINSTANCE g_instance = NULL;
	HANDLE g_act_ctx = NULL;
}

class actctx_activator
{
protected:
	ULONG_PTR m_cookie; // Cookie for context deactivation

public:
	// Constructs the activator and activates the given activation context
	actctx_activator(_In_ HANDLE hActCtx)
	{
		if (!ActivateActCtx(hActCtx, &m_cookie))
			m_cookie = 0;
	}

	// Deactivates activation context and destructs the activator
	virtual ~actctx_activator()
	{
		if (m_cookie)
			DeactivateActCtx(0, m_cookie);
	}
};

BOOL WINAPI DllMain(_In_ HINSTANCE hinstDLL, _In_ DWORD fdwReason, _In_ LPVOID lpvReserved)
{
	UNREFERENCED_PARAMETER(lpvReserved);

	if (fdwReason == DLL_PROCESS_ATTACH) 
	{
		g_instance = hinstDLL;			// Save DLL's instance handle
		GetCurrentActCtx(&g_act_ctx);	// Save current activation context
	}
	else if (fdwReason == DLL_PROCESS_DETACH) 
	{
		if (g_act_ctx)
			ReleaseActCtx(g_act_ctx);
	}

	return TRUE;
}

DWORD ShowConfigUI(const std::string& iniPath, HWND Parent)
{
	actctx_activator actctx(g_act_ctx);	// Restore plugin's activation context

	new wxApp();
	wxEntryStart(g_instance);

	int result;
	{
		wxWindow parent;						// Create wxWidget-approved parent window
		parent.SetHWND((WXHWND)Parent);
		parent.AdoptAttributesFromHWND();
		wxTopLevelWindows.Append(&parent);

		SettingsDialog dlg(&parent, iniPath);	// Create and launch configuration dialog
		result = dlg.ShowModal();

		wxTopLevelWindows.DeleteObject(&parent);
		parent.SetHWND((WXHWND)NULL);
	}

	wxEntryCleanup();
	return result == wxID_OK ? ERROR_SUCCESS : ERROR_CANCELLED;
}

std::string GetModulePath()	// keep backslash at the end
{
	char iniFilePath[MAX_PATH];
	GetModuleFileNameA(g_instance, iniFilePath, MAX_PATH);
	char* dot = strrchr(iniFilePath, '\\');
	dot[1] = 0;
	
	return iniFilePath;
}