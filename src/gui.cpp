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

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Sampling rate"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer6->Add( m_staticText3, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxArrayString cbSamplingRateChoices;
	cbSamplingRate = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, cbSamplingRateChoices, 0, wxDefaultValidator, wxT("cbSamplingRate") );
	cbSamplingRate->SetSelection( 0 );
	bSizer6->Add( cbSamplingRate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	chkStereo = new wxCheckBox( this, wxID_ANY, wxT("Stereo"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("chkStereo") );
	bSizer6->Add( chkStereo, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer1->Add( bSizer6, 1, wxEXPAND, 5 );

	nbTabs = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, wxT("nbTabs") );
	m_panel1 = new wxPanel( nbTabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 1, 2, 0, 0 );

	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( m_panel1, wxID_ANY, wxEmptyString ), wxVERTICAL );

	cbMp3Cbr = new wxCheckBox( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Constant bitrate (CBR)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("cbMp3Cbr") );
	sbSizer1->Add( cbMp3Cbr, 0, wxALL, 5 );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText4 = new wxStaticText( sbSizer1->GetStaticBox(), wxID_ANY, wxT("Target bitrate"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer4->Add( m_staticText4, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxArrayString cbMp3CbrRatesChoices;
	cbMp3CbrRates = new wxChoice( sbSizer1->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, cbMp3CbrRatesChoices, 0, wxDefaultValidator, wxT("cbMp3CbrRates") );
	cbMp3CbrRates->SetSelection( 0 );
	bSizer4->Add( cbMp3CbrRates, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	sbSizer1->Add( bSizer4, 1, wxEXPAND, 5 );


	gSizer1->Add( sbSizer1, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( m_panel1, wxID_ANY, wxEmptyString ), wxVERTICAL );

	cbMp3Vbr = new wxCheckBox( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Variable bitrate (VBR)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("cbMp3Vbr") );
	sbSizer2->Add( cbMp3Vbr, 0, wxALL, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText5 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Target quality"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer5->Add( m_staticText5, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxArrayString cbMp3VbrQualityChoices;
	cbMp3VbrQuality = new wxChoice( sbSizer2->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, cbMp3VbrQualityChoices, 0, wxDefaultValidator, wxT("cbMp3VbrQuality") );
	cbMp3VbrQuality->SetSelection( 0 );
	bSizer5->Add( cbMp3VbrQuality, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	sbSizer2->Add( bSizer5, 1, wxEXPAND, 5 );


	gSizer1->Add( sbSizer2, 1, wxEXPAND, 5 );


	m_panel1->SetSizer( gSizer1 );
	m_panel1->Layout();
	gSizer1->Fit( m_panel1 );
	nbTabs->AddPage( m_panel1, wxT("MP3"), false );
	m_panel2 = new wxPanel( nbTabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxGridSizer* gSizer11;
	gSizer11 = new wxGridSizer( 1, 2, 0, 0 );

	wxStaticBoxSizer* sbSizer11;
	sbSizer11 = new wxStaticBoxSizer( new wxStaticBox( m_panel2, wxID_ANY, wxEmptyString ), wxVERTICAL );

	cbOggAbr = new wxCheckBox( sbSizer11->GetStaticBox(), wxID_ANY, wxT("Average bitrate (ABR)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("cbOggAbr") );
	sbSizer11->Add( cbOggAbr, 0, wxALL, 5 );

	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText41 = new wxStaticText( sbSizer11->GetStaticBox(), wxID_ANY, wxT("Target bitrate"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	bSizer41->Add( m_staticText41, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxArrayString cbOggAbrRatesChoices;
	cbOggAbrRates = new wxChoice( sbSizer11->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, cbOggAbrRatesChoices, 0, wxDefaultValidator, wxT("cbOggAbrRates") );
	cbOggAbrRates->SetSelection( 0 );
	bSizer41->Add( cbOggAbrRates, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	sbSizer11->Add( bSizer41, 1, wxEXPAND, 5 );


	gSizer11->Add( sbSizer11, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer21;
	sbSizer21 = new wxStaticBoxSizer( new wxStaticBox( m_panel2, wxID_ANY, wxEmptyString ), wxVERTICAL );

	cbOggVbr = new wxCheckBox( sbSizer21->GetStaticBox(), wxID_ANY, wxT("Variable bitrate (VBR)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, wxT("cbOggVbr") );
	sbSizer21->Add( cbOggVbr, 0, wxALL, 5 );

	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText51 = new wxStaticText( sbSizer21->GetStaticBox(), wxID_ANY, wxT("Target quality"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText51->Wrap( -1 );
	bSizer51->Add( m_staticText51, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxArrayString cbOggVbrQuality1Choices;
	cbOggVbrQuality1 = new wxChoice( sbSizer21->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, cbOggVbrQuality1Choices, 0, wxDefaultValidator, wxT("cbMp3VbrQuality") );
	cbOggVbrQuality1->SetSelection( 0 );
	bSizer51->Add( cbOggVbrQuality1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	sbSizer21->Add( bSizer51, 1, wxEXPAND, 5 );


	gSizer11->Add( sbSizer21, 1, wxEXPAND, 5 );


	m_panel2->SetSizer( gSizer11 );
	m_panel2->Layout();
	gSizer11->Fit( m_panel2 );
	nbTabs->AddPage( m_panel2, wxT("OGG"), true );

	bSizer1->Add( nbTabs, 1, wxEXPAND | wxALL, 5 );

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
	cbMp3Cbr->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( SettingsDialogGui::cbMp3Cbr_Click ), NULL, this );
	cbMp3Vbr->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( SettingsDialogGui::cbMp3Vbr_Click ), NULL, this );
	cbOggAbr->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( SettingsDialogGui::cbOggAbr_Click ), NULL, this );
	cbOggVbr->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( SettingsDialogGui::cbOggVbr_Click ), NULL, this );
	btnOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsDialogGui::btnOK_Click ), NULL, this );
}

SettingsDialogGui::~SettingsDialogGui()
{
	// Disconnect Events
	cbMp3Cbr->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( SettingsDialogGui::cbMp3Cbr_Click ), NULL, this );
	cbMp3Vbr->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( SettingsDialogGui::cbMp3Vbr_Click ), NULL, this );
	cbOggAbr->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( SettingsDialogGui::cbOggAbr_Click ), NULL, this );
	cbOggVbr->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( SettingsDialogGui::cbOggVbr_Click ), NULL, this );
	btnOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsDialogGui::btnOK_Click ), NULL, this );

}
