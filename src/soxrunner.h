#pragma once
#include <windows.h>
#include <string>
#include "inifileext.h"
#include "guirunner.h"
#include "utils.h"

class SoxRunner
{
public:
	SoxRunner(std::wstring& infile, std::wstring& outfile, IniFileExt& ini);
	bool Process();

private:
	bool runSox();
	void testPercents(const char* chBuf, const char* pPtr);
	void buildCustomArgs(IniFileExt& ini);
	void buildCommandLine(IniFileExt& ini);
	void addCustomFlag(const std::string& flag);
	void addCustomArgument(const std::string& arg, const std::string& value);
	void addCustomArgument(const std::string& arg, int value);

	std::wstring mSoxFolder;
	std::wstring mInfile, mOutfile;
	std::vector<std::string> mSupportedTypes;
	std::string mCustomArgs;
	std::wstring mCommandLine;
};
