#include "settingsdialog.h"
#include <sstream>

SettingsDialog::SettingsDialog(wxWindow* parent, const std::string& iniPath)
: SettingsDialogGui(parent), mConfig("", "", iniPath)
{
	setDialogItemFromConfig(mConfig, "alwaysShow", true, chkAlwaysShow);
	setDialogItemFromConfig(mConfig, "isStereo", true, chkStereo);
	setDialogItemFromConfig(mConfig, "isNormalize", true, chkNormalize);
	setDialogItemFromConfig(mConfig, "fileTypes", "CDDA|CDR|FLAC|GSM|MP2|MP3|OGG|WAV", "fileType", 0, cbFormats);
	setDialogItemFromConfig(mConfig, "sampleRates", "11025|22050|44100", "sampleRate", 0, cbSamplingRate);
	setDialogItemFromConfig(mConfig, "mp3Modes", "CBR|VBR", "mp3Mode", 0, cbMp3Modes);
	setDialogItemFromConfig(mConfig, "mp3CbrBitrates", "64|96|128|192|256|320", "mp3CbrBitrate", 0, cbMp3CbrRates);
	setDialogItemFromConfig(mConfig, "mp3VbrQualities", "Very high|High|Normal|Low|Very low", "mp3VbrQuality", 0, cbMp3VbrQuality);
}

void SettingsDialog::btnOK_Click(wxCommandEvent &)
{
	mConfig.Write("alwaysShow", chkAlwaysShow->IsChecked());
	mConfig.Write("isStereo", chkStereo->IsChecked());
	mConfig.Write("isNormalize", chkNormalize->IsChecked());
	mConfig.Write("fileType", cbFormats->GetSelection());
	mConfig.Write("sampleRate", cbSamplingRate->GetSelection());
	mConfig.Write("mp3Mode", cbMp3Modes->GetSelection());
	mConfig.Write("mp3CbrBitrate", cbMp3CbrRates->GetSelection());
	mConfig.Write("mp3VbrQuality", cbMp3VbrQuality->GetSelection());
	EndModal(wxID_OK);
}

void SettingsDialog::setDialogItemFromConfig(const wxFileConfig& config, const wxString& key, const wxString& defValues, 
											 const wxString& defValueKey, int defValueIndex, wxChoice* cbChoice)
{
	int index;
	wxString value;
	config.Read(key, &value, defValues);
	config.Read(defValueKey, &index, defValueIndex);

	std::string valueStr = std::string(value);
	std::stringstream ss(valueStr);
	std::string token;
	cbChoice->Clear();
	while (std::getline(ss, token, '|'))
		cbChoice->Append(token);
	cbChoice->SetSelection(index);
}

void SettingsDialog::setDialogItemFromConfig(const wxFileConfig& config, const wxString& key, bool defValue, wxCheckBox* chkBox)
{
	bool value;
	config.Read(key, &value, defValue);
	chkBox->SetValue(value);
}
