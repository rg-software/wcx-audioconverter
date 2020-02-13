///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui.h"

///////////////////////////////////////////////////////////////////////////

SettingsDialogGui::SettingsDialogGui( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	nbTabs = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel1 = new wxPanel( nbTabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 3, 4, 0, 0 );

	m_staticText1 = new wxStaticText( m_panel1, wxID_ANY, wxT("Target format"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	gSizer1->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxArrayString cbFormatsChoices;
	cbFormats = new wxChoice( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, cbFormatsChoices, 0, wxDefaultValidator, wxT("cbFormats") );
	cbFormats->SetSelection( 0 );
	gSizer1->Add( cbFormats, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText2 = new wxStaticText( m_panel1, wxID_ANY, wxT("MP3 mode"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	gSizer1->Add( m_staticText2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxArrayString cbMp3ModesChoices;
	cbMp3Modes = new wxChoice( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, cbMp3ModesChoices, 0, wxDefaultValidator, wxT("cbMp3Modes") );
	cbMp3Modes->SetSelection( 0 );
	gSizer1->Add( cbMp3Modes, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText3 = new wxStaticText( m_panel1, wxID_ANY, wxT("Sampling rate"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	gSizer1->Add( m_staticText3, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxArrayString cbSamplingRateChoices;
	cbSamplingRate = new wxChoice( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, cbSamplingRateChoices, 0, wxDefaultValidator, wxT("cbSamplingRate") );
	cbSamplingRate->SetSelection( 0 );
	gSizer1->Add( cbSamplingRate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText4 = new wxStaticText( m_panel1, wxID_ANY, wxT("MP3 CBR bitrate"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	gSizer1->Add( m_staticText4, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxArrayString cbMp3CbrRatesChoices;
	cbMp3CbrRates = new wxChoice( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, cbMp3CbrRatesChoices, 0, wxDefaultValidator, wxT("cbMp3CbrRates") );
	cbMp3CbrRates->SetSelection( 0 );
	gSizer1->Add( cbMp3CbrRates, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	gSizer1->Add( 0, 0, 1, wxEXPAND, 5 );


	gSizer1->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText5 = new wxStaticText( m_panel1, wxID_ANY, wxT("MP3 VBR quality"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	gSizer1->Add( m_staticText5, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxArrayString cbMp3VbrQualityChoices;
	cbMp3VbrQuality = new wxChoice( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, cbMp3VbrQualityChoices, 0, wxDefaultValidator, wxT("cbMp3VbrQuality") );
	cbMp3VbrQuality->SetSelection( 0 );
	gSizer1->Add( cbMp3VbrQuality, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	m_panel1->SetSizer( gSizer1 );
	m_panel1->Layout();
	gSizer1->Fit( m_panel1 );
	nbTabs->AddPage( m_panel1, wxT("MP3"), true );
	m_panel2 = new wxPanel( nbTabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	nbTabs->AddPage( m_panel2, wxT("a page"), false );

	bSizer1->Add( nbTabs, 1, wxEXPAND | wxALL, 5 );

	chkStereo = new wxCheckBox( this, wxID_ANY, wxT("Stereo"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("chkStereo") );
	bSizer1->Add( chkStereo, 0, wxALL, 5 );

	chkNormalize = new wxCheckBox( this, wxID_ANY, wxT("Normalize"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("chkNormalize") );
	bSizer1->Add( chkNormalize, 0, wxALL, 5 );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );

	chkAlwaysShow = new wxCheckBox( this, wxID_ANY, wxT("Always show this dialog"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("chkAlwaysShow") );
	bSizer2->Add( chkAlwaysShow, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	btnOK = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( btnOK, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	btnCancel = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( btnCancel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer1->Add( bSizer2, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	btnOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsDialogGui::btnOK_Click ), NULL, this );
}

SettingsDialogGui::~SettingsDialogGui()
{
	// Disconnect Events
	btnOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsDialogGui::btnOK_Click ), NULL, this );

}
