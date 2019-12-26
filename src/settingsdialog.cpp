#include "settingsdialog.h"
#include "utils.h"
#include <sstream>

SettingsDialog::SettingsDialog(wxWindow* parent, const std::wstring& iniPath)
: SettingsDialogGui(parent), mConfig(to_string(iniPath))
{
	setDialogItemFromConfig("alwaysShow", chkAlwaysShow);
	setDialogItemFromConfig("isStereo", chkStereo);
	setDialogItemFromConfig("isNormalize", chkNormalize);
	setDialogItemFromConfig("fileTypes", "fileType", cbFormats);
	setDialogItemFromConfig("sampleRates", "sampleRate", cbSamplingRate);
	setDialogItemFromConfig("mp3Modes",  "mp3Mode", cbMp3Modes);
	setDialogItemFromConfig("mp3CbrBitrates", "mp3CbrBitrate", cbMp3CbrRates);
	setDialogItemFromConfig("mp3VbrQualities", "mp3VbrQuality", cbMp3VbrQuality);
}

void SettingsDialog::btnOK_Click(wxCommandEvent &)
{
	mConfig.SetInteger("alwaysShow", chkAlwaysShow->IsChecked());
	mConfig.SetInteger("isStereo", chkStereo->IsChecked());
	mConfig.SetInteger("isNormalize", chkNormalize->IsChecked());
	mConfig.SetInteger("fileType", cbFormats->GetSelection());
	mConfig.SetInteger("sampleRate", cbSamplingRate->GetSelection());
	mConfig.SetInteger("mp3Mode", cbMp3Modes->GetSelection());
	mConfig.SetInteger("mp3CbrBitrate", cbMp3CbrRates->GetSelection());
	mConfig.SetInteger("mp3VbrQuality", cbMp3VbrQuality->GetSelection());
	mConfig.Write();
	EndModal(wxID_OK);
}

void SettingsDialog::setDialogItemFromConfig(const std::string& key, const std::string& defValueKey, wxChoice* cbChoice)
{
	int index = mConfig.GetInteger(defValueKey);
	auto valueList = mConfig.GetStringList(key);

	cbChoice->Clear();
	for(const auto& v : valueList)
		cbChoice->Append(v);
	cbChoice->SetSelection(index);
}

void SettingsDialog::setDialogItemFromConfig(const std::string& key, wxCheckBox* chkBox)
{
	chkBox->SetValue(mConfig.GetInteger(key));
}
