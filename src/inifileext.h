#pragma once
#include "ini.h"

class IniFileExt
{
public:
    IniFileExt(const std::string& iniPath) : mIniFile(iniPath)
    {
		mIniFile.read(mIni);
    }

	std::string GetString(const std::string& key, const std::string& section = "")
	{
		return mIni[section][key];
	}

	void SetString(const std::string& key, const std::string& value, const std::string& section = "")
	{
		mIni[section][key] = value;
	}

	int GetInteger(const std::string& key, const std::string& section = "")
    {
		return std::atoi(GetString(key, section).c_str());
    }

	void SetInteger(const std::string& key, int value, const std::string& section = "")
	{
		SetString(key, std::to_string(value), section);
	}

	std::vector<std::string> GetStringList(const std::string& key, const std::string& section = "")
    {
		std::string valueStr = GetString(key, section);

		std::stringstream ss(valueStr);
		std::string token;
		std::vector<std::string> values;
		while (std::getline(ss, token, '|'))
			values.push_back(token);
		return values;
    }

	std::string GetStringItem(const std::string& listKey, const std::string& indexKey, const std::string& section = "")
    {
		return GetStringList(listKey, section)[GetInteger(indexKey, section)];
    }

	void Write()
    {
		mIniFile.write(mIni);
    }

private:
    mINI::INIFile mIniFile;
	mINI::INIStructure mIni;
};