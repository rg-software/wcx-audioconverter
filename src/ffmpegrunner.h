#pragma once
#include <windows.h>

#ifndef WCXHEAD_INCLUDED
#define WCXHEAD_INCLUDED
#include "wcxhead.h"
#endif

#include "inifileext.h"
#include "guirunner.h"
#include "utils.h"
#include <string>
#include <map>
#include <functional>

class FfmpegRunner
{
public:
	FfmpegRunner(wchar_t* srcPath, wchar_t* filePath, std::wstring& outfile, IniFileExt& ini, tProcessDataProcW processDataProc);
	bool Process() const;
	
	void AddCustomFlag(const std::string& flag);
	void AddCustomArgument(const std::string& arg, const std::string& value);
	void AddCustomArgument(const std::string& arg, int value);

private:
	bool runFfmpeg() const;
	static unsigned getTimeValue(unsigned prevValue, const char* pattern, const char* chBuf);

	std::map<std::string, std::function<std::wstring(FfmpegRunner&, IniFileExt &)>> mCustomArgsAdders;
	tProcessDataProcW mProcessDataProc;
	wchar_t* mSrcPath;
	std::wstring mFfmpegFolder;
	std::wstring mInfile, mOutfile;
	std::vector<std::string> mSupportedTypes;
	std::string mCustomArgs;
	std::wstring mCommandLine;
};
