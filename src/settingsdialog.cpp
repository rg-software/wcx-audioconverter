#include "settingsdialog.h"

SettingsDialog::SettingsDialog(wxWindow* parent, const std::string& iniPath)
: SettingsDialogGui(parent)
{
	//SetTitle(iniPath);
	wxFileConfig config("", "", iniPath);

	setDialogItemFromConfig(config, "alwaysShow", chkAlwaysShow, true);

	//bool alwaysShow;
	//config.Read("alwaysShow", &alwaysShow, true);

	//config.Write("alwaysShow", alwaysShow);


}

void SettingsDialog::setDialogItemFromConfig(const wxFileConfig& config, const wxString& key, wxCheckBox* chkBox, bool defValue)
{
	bool value;
	config.Read(key, &value, defValue);
	chkBox->SetValue(value);
}
