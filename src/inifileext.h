#pragma once
#include "ini.h"

class IniFileExt
{
public:
    IniFileExt(const std::string& iniPath) : mIniFile(iniPath)
    {
		mIniFile.read(mIni);
    }

	int GetInteger(const std::string& key)
    {
		return std::atoi(GetString(key).c_str());
    }

	std::string GetString(const std::string& key)
    {
		return mIni[""][key];
    }

	std::vector<std::string> GetStringList(const std::string& key)
    {
		std::string valueStr = GetString(key);

		std::stringstream ss(valueStr);
		std::string token;
		std::vector<std::string> values;
		while (std::getline(ss, token, '|'))
			values.push_back(token);
		return values;
    }

	std::string GetStringItem(const std::string& listKey, const std::string& indexKey)
    {
		return GetStringList(listKey)[GetInteger(indexKey)];
    }

	void SetInteger(const std::string& key, int value)
    {
		SetString(key, std::to_string(value));
    }

	void SetString(const std::string& key, const std::string& value)
    {
		mIni[""][key] = value;
    }

	void Write()
    {
		mIniFile.write(mIni);
    }

private:
    mINI::INIFile mIniFile;
	mINI::INIStructure mIni;
};