#include "soxrunner.h"

SoxRunner::SoxRunner(std::wstring& infile, std::wstring& outfile, IniFileExt& ini)
: mSoxFolder(join_paths(to_wstring(GetModulePath()), std::wstring(L"Sox")))
{
	mInfile = infile;
	mOutfile = outfile;
	mSupportedTypes = ini.GetStringList("fileTypes");
	buildCommandLine(ini);
}

void SoxRunner::buildCommandLine(class IniFileExt& ini)
{
	buildCustomArgs(ini);
	mCommandLine = quote(join_paths(mSoxFolder, std::wstring(L"sox.exe"))) + L" " +
				   quote(mInfile) + L" " + 
				   to_wstring(mCustomArgs) + L" " +
				   quote(mOutfile);
}

void SoxRunner::buildCustomArgs(IniFileExt& ini)
{
	if (ini.GetInteger("isNormalize"))
		addCustomFlag("--norm");

	// currently we only support MP3
	if (ini.GetStringItem("fileTypes", "fileType") == std::string("MP3"))
	{
		addCustomArgument("--channels", ini.GetInteger("isStereo") ? 2 : 1);

		if (ini.GetStringItem("mp3Modes", "mp3Mode") == std::string("CBR")) // set bitrate ("128", "256")
			addCustomArgument("-C", ini.GetStringItem("mp3CbrBitrates", "mp3CbrBitrate"));
		else // VBR: set quality as -0..-9	// $mm TODO: double check!
			addCustomArgument("-C", std::to_string(ini.GetInteger("mp3VbrQuality") * 2));
	}
}

void SoxRunner::addCustomFlag(const std::string& flag)
{
	mCustomArgs += " " + flag;
}

void SoxRunner::addCustomArgument(const std::string& arg, const std::string& value)
{
	mCustomArgs += " " + arg + " " + value;
}

void SoxRunner::addCustomArgument(const std::string& arg, int value)
{
	addCustomArgument(arg, std::to_string(value));
}

bool SoxRunner::runSox()
{
	// cmdline must not be const for CreateProcess()
	// use "-S" first to display progress (last line: In:nn%)
	// rely on https://docs.microsoft.com/en-us/windows/win32/procthread/creating-a-child-process-with-redirected-input-and-output
	// for stderr redirection

	std::vector<wchar_t> cmdLineBuf(mCommandLine.length() + 1, L'\0');
	std::copy_n(mCommandLine.begin(), mCommandLine.length(), cmdLineBuf.begin());

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	CreateProcess(NULL, &cmdLineBuf[0], NULL, NULL, false,
	              CREATE_NO_WINDOW, NULL, mSoxFolder.c_str(), &si, &pi);

	WaitForSingleObject(pi.hProcess, INFINITE);

	DWORD exit_code;
	GetExitCodeProcess(pi.hProcess, &exit_code);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return exit_code == 0;
}

bool SoxRunner::Process()
{
	for (const auto& var_type : mSupportedTypes)
		if (ends_with(to_lower(mInfile), to_lower(L"." + to_wstring(var_type))))
			return runSox();
	return true;
}
