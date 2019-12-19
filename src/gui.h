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
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class SettingsDialogGui
///////////////////////////////////////////////////////////////////////////////
class SettingsDialogGui : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText1;
		wxChoice* cbFormats;
		wxStaticText* m_staticText2;
		wxChoice* cbMp3Modes;
		wxStaticText* m_staticText3;
		wxChoice* cbSamplingRate;
		wxStaticText* m_staticText4;
		wxChoice* cbMp3CbrRates;
		wxStaticText* m_staticText5;
		wxChoice* cbMp3VbrQuality;
		wxCheckBox* chkStereo;
		wxCheckBox* chkNormalize;
		wxCheckBox* chkAlwaysShow;
		wxButton* btnOK;
		wxButton* btnCancel;

		// Virtual event handlers, overide them in your derived class
		virtual void btnOK_Click( wxCommandEvent& event ) { event.Skip(); }


	public:

		SettingsDialogGui( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Audioconverter"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 622,257 ), long style = wxDEFAULT_DIALOG_STYLE );
		~SettingsDialogGui();

};

