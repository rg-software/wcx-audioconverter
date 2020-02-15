#include "settingsdialog.h"
#include "utils.h"
#include <sstream>
#include <wx/persist/treebook.h>
#include <wx/persist.h>
#include <wx/persist/toplevel.h>
#include <wx/persist/window.h>
#include <wx/wfstream.h>

SettingsDialog::SettingsDialog(wxWindow* parent, const std::string& iniPath)
: SettingsDialogGui(parent), mConfig(iniPath)
{
	mSavers = { std::make_pair("wxCheckBox", &SettingsDialog::saveCheckBox),
				std::make_pair("wxChoice", &SettingsDialog::saveChoice),
				std::make_pair("wxNotebook", &SettingsDialog::saveNotebook) };

	mLoaders = { std::make_pair("wxCheckBox", &SettingsDialog::loadCheckBox),
				 std::make_pair("wxChoice", &SettingsDialog::loadChoice),
				 std::make_pair("wxNotebook", &SettingsDialog::loadNotebook) };

	loadChildren(this);
}

void SettingsDialog::loadChildren(wxWindow* parent)
{
	for (auto it : parent->GetChildren())
	{
		loadControl(it);
		loadChildren(it);
	}
}

void SettingsDialog::saveCheckBox(wxWindow* chkBox)
{
	wxCheckBox* cb = dynamic_cast<wxCheckBox*>(chkBox);
	mConfig.SetInteger("IsChecked", cb->IsChecked(), cb->GetName().ToStdString());
}

void SettingsDialog::saveChoice(wxWindow* cbChoice)	// we need to save the current selection only
{
	wxChoice* cb = dynamic_cast<wxChoice*>(cbChoice);
	mConfig.SetInteger("Selection", cb->GetSelection(), cb->GetName().ToStdString());
}

void SettingsDialog::saveNotebook(wxWindow* book)
{
	wxNotebook* wb = dynamic_cast<wxNotebook*>(book);
	mConfig.SetInteger("Selection", wb->GetSelection(), wb->GetName().ToStdString());
}

void SettingsDialog::loadCheckBox(wxWindow* chkBox)
{
	wxCheckBox* cb = dynamic_cast<wxCheckBox*>(chkBox);
	cb->SetValue(mConfig.GetInteger("IsChecked", cb->GetName().ToStdString()));
}

void SettingsDialog::loadChoice(wxWindow* cbChoice)
{
	wxChoice* cb = dynamic_cast<wxChoice*>(cbChoice);
	auto valueList = mConfig.GetStringList("Items", cb->GetName().ToStdString());

	cb->Clear();
	for (const auto& v : valueList)
		cb->Append(v);
	cb->SetSelection(mConfig.GetInteger("Selection", cb->GetName().ToStdString()));
}

void SettingsDialog::loadNotebook(wxWindow* book)
{
	wxNotebook* wb = dynamic_cast<wxNotebook*>(book);
	wb->SetSelection(mConfig.GetInteger("Selection", wb->GetName().ToStdString()));
}

void SettingsDialog::saveControl(wxWindow* ctrl)
{
	wxString className(ctrl->GetClassInfo()->GetClassName());
	
	if (mSavers.find(className) != mSavers.end())
		mSavers.find(className)->second(this, ctrl);
}

void SettingsDialog::loadControl(wxWindow* ctrl)
{
	wxString className(ctrl->GetClassInfo()->GetClassName());

	if (mLoaders.find(className) != mLoaders.end())
		mLoaders.find(className)->second(this, ctrl);
}

void SettingsDialog::saveChildren(wxWindow* parent)
{
	for (auto it : parent->GetChildren())
	{
		saveControl(it);
		saveChildren(it);
	}
}

void SettingsDialog::btnOK_Click(wxCommandEvent &)
{
	saveChildren(this);
	mConfig.Write();
	EndModal(wxID_OK);
}

void SettingsDialog::cbMp3Cbr_Click(wxCommandEvent& event) 
{
	cbMp3Vbr->SetValue(!cbMp3Cbr->GetValue());
}

void SettingsDialog::cbMp3Vbr_Click(wxCommandEvent& event)
{ 
	cbMp3Cbr->SetValue(!cbMp3Vbr->GetValue());
}
