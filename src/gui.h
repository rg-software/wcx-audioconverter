///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/checkbox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class SettingsDialogGui
///////////////////////////////////////////////////////////////////////////////
class SettingsDialogGui : public wxDialog
{
	private:

	protected:
		wxCheckBox* m_checkBox1;
		wxButton* m_button1;
		wxButton* m_button2;

	public:

		SettingsDialogGui( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Audioconverter"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 622,312 ), long style = wxDEFAULT_DIALOG_STYLE );
		~SettingsDialogGui();

};

