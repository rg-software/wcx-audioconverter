#include <wx/wxprec.h>
#include <wx/app.h> 
#include <wx/dynlib.h>
#include <wx/msw/wrapwin.h>
#include <process.h>

#include "settingsdialog.h"

HINSTANCE g_instance = NULL;
HANDLE g_act_ctx = NULL;

class actctx_activator
{
protected:
	ULONG_PTR m_cookie; // Cookie for context deactivation

public:
	// Construct the activator and activates the given activation context
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
		// Save DLL's instance handle.
		g_instance = hinstDLL;

		// Save current activation context.
		GetCurrentActCtx(&g_act_ctx);
	}
	else if (fdwReason == DLL_PROCESS_DETACH) 
	{
		if (g_act_ctx)
			ReleaseActCtx(g_act_ctx);
	}

	return TRUE;
}

DWORD ShowConfigUI(const char* iniPath, HWND Parent)
{
	// Restore plugin's activation context.
	actctx_activator actctx(g_act_ctx);

	// Initialize application.
	new wxApp();
	wxEntryStart(g_instance);

	int result;
	{
		// Create wxWidget-approved parent window.
		wxWindow parent;
		parent.SetHWND((WXHWND)Parent);
		parent.AdoptAttributesFromHWND();
		wxTopLevelWindows.Append(&parent);

		// Create and launch configuration dialog.
		SettingsDialog dlg(&parent, iniPath);
		result = dlg.ShowModal();

		wxTopLevelWindows.DeleteObject(&parent);
		parent.SetHWND((WXHWND)NULL);
	}

	// Clean-up and return.
	wxEntryCleanup();
	return result == wxID_OK ? ERROR_SUCCESS : ERROR_CANCELLED;
}
