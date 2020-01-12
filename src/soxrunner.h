#pragma once
#include <windows.h>

#ifndef WCXHEAD_INCLUDED
#define WCXHEAD_INCLUDED
#include "wcxhead.h"
#endif

#include <string>
#include "inifileext.h"
#include "guirunner.h"
#include "utils.h"

class SoxRunner
{
public:
	SoxRunner(wchar_t* srcPath, wchar_t* filePath, std::wstring& outfile, IniFileExt& ini, tProcessDataProcW processDataProc);
	bool Process() const;

private:
	bool runSox() const;
	static unsigned extractPercents(unsigned prevValue, const char* chBuf);
	void buildCustomArgs(IniFileExt& ini);
	void buildCommandLine(IniFileExt& ini);
	void addCustomFlag(const std::string& flag);
	void addCustomArgument(const std::string& arg, const std::string& value);
	void addCustomArgument(const std::string& arg, int value);

	tProcessDataProcW mProcessDataProc;
	wchar_t* mSrcPath;
	std::wstring mSoxFolder;
	std::wstring mInfile, mOutfile;
	std::vector<std::string> mSupportedTypes;
	std::string mCustomArgs;
	std::wstring mCommandLine;
};
