#include "settingsdialog.h"
#include <sstream>

SettingsDialog::SettingsDialog(wxWindow* parent, const std::string& iniPath)
: SettingsDialogGui(parent), mIniFile(iniPath)
{
	mIniFile.read(mConfig);
	setDialogItemFromConfig("alwaysShow", true, chkAlwaysShow);
	setDialogItemFromConfig("isStereo", true, chkStereo);
	setDialogItemFromConfig("isNormalize", true, chkNormalize);
	setDialogItemFromConfig("fileTypes", "CDDA|CDR|FLAC|GSM|MP2|MP3|OGG|WAV", "fileType", 0, cbFormats);
	setDialogItemFromConfig("sampleRates", "11025|22050|44100", "sampleRate", 0, cbSamplingRate);
	setDialogItemFromConfig("mp3Modes", "CBR|VBR", "mp3Mode", 0, cbMp3Modes);
	setDialogItemFromConfig("mp3CbrBitrates", "64|96|128|192|256|320", "mp3CbrBitrate", 0, cbMp3CbrRates);
	setDialogItemFromConfig("mp3VbrQualities", "Very high|High|Normal|Low|Very low", "mp3VbrQuality", 0, cbMp3VbrQuality);
}

void SettingsDialog::btnOK_Click(wxCommandEvent &)
{
	mConfig[""]["alwaysShow"] = std::to_string(chkAlwaysShow->IsChecked());
	mConfig[""]["isStereo"] = std::to_string(chkStereo->IsChecked());
	mConfig[""]["isNormalize"] = std::to_string(chkNormalize->IsChecked());
	mConfig[""]["fileType"] = std::to_string(cbFormats->GetSelection());
	mConfig[""]["sampleRate"] = std::to_string(cbSamplingRate->GetSelection());
	mConfig[""]["mp3Mode"] = std::to_string(cbMp3Modes->GetSelection());
	mConfig[""]["mp3CbrBitrate"] = std::to_string(cbMp3CbrRates->GetSelection());
	mConfig[""]["mp3VbrQuality"] = std::to_string(cbMp3VbrQuality->GetSelection());
	mIniFile.write(mConfig);
	EndModal(wxID_OK);
}

void SettingsDialog::setDialogItemFromConfig(const std::string& key, const std::string& defValues,
											 const std::string& defValueKey, int defValueIndex, wxChoice* cbChoice)
{
	int index = mConfig[""].has(defValueKey) ? std::atoi(mConfig[""][defValueKey].c_str()) : defValueIndex;
	std::string valueStr = mConfig[""].has(key) ? mConfig[""][key] : defValues;
	
	std::stringstream ss(valueStr);
	std::string token;
	cbChoice->Clear();
	while (std::getline(ss, token, '|'))
		cbChoice->Append(token);
	cbChoice->SetSelection(index);
}

void SettingsDialog::setDialogItemFromConfig(const std::string& key, bool defValue, wxCheckBox* chkBox)
{
	bool value = mConfig[""].has(key) ? std::atoi(mConfig[""][key].c_str()) : defValue;
	chkBox->SetValue(value);
}
