#include "ffmpegrunner.h"

FfmpegRunner::FfmpegRunner(wchar_t* srcPath, wchar_t* filePath, std::wstring& outfile, IniFileExt& ini, tProcessDataProcW processDataProc)
: mFfmpegFolder(join_paths(to_wstring(GetModulePath()), std::wstring(L"."))), mSrcPath(srcPath), mProcessDataProc(processDataProc)
{
	// here outfile still has its original extension
	mCustomArgsAdders = { std::make_pair("MP3", &FfmpegRunner::addCustomArgsMP3) };

	std::string currentTab = ini.GetStringItem("Items", "Selection", "nbTabs");
	std::wstring outExtension = L"out";
	
	if (mCustomArgsAdders.find(currentTab) != mCustomArgsAdders.end())
		outExtension = mCustomArgsAdders.find(currentTab)->second(this, ini);

	mSupportedTypes = ini.GetStringList("Items", "Extensions");
	mInfile = join_paths(std::wstring(srcPath), std::wstring(filePath));
	mOutfile = change_extension(outfile, outExtension);

	mCommandLine = quote(join_paths(mFfmpegFolder, std::wstring(L"ffmpeg.exe"))) + L" -y -i " +
		quote(mInfile) + L" " +
		to_wstring(mCustomArgs) + L" " +
		quote(mOutfile);


	// MessageBox(0, mCommandLine.c_str(), L"", 0);
}

void FfmpegRunner::addCustomArgsGlobal(IniFileExt& ini)
{
	addCustomArgument("-ar", ini.GetStringItem("Items", "Selection", "cbSamplingRate"));
	addCustomArgument("-ac", ini.GetInteger("IsChecked", "chkStereo") ? 2 : 1);
}

std::wstring FfmpegRunner::addCustomArgsMP3(IniFileExt& ini)
{
	addCustomArgument("-codec:a", "libmp3lame");

	if (ini.GetInteger("IsChecked", "cbMp3Cbr"))
		addCustomArgument("-b:a", ini.GetStringItem("Items", "Selection", "cbMp3CbrRates"));
	else // for VBR
		addCustomArgument("-qscale:a", ini.GetInteger("Selection", "cbMp3VbrQuality") * 2); // range is 0-9 where a lower value is a higher quality

	return L"mp3";
}

void FfmpegRunner::addCustomFlag(const std::string& flag)
{
	mCustomArgs += " " + flag;
}

void FfmpegRunner::addCustomArgument(const std::string& arg, const std::string& value)
{
	mCustomArgs += " " + arg + " " + value;
}

void FfmpegRunner::addCustomArgument(const std::string& arg, int value)
{
	addCustomArgument(arg, std::to_string(value));
}

unsigned FfmpegRunner::getTimeValue(unsigned prevValue, const char* pattern, const char* chBuf)
{
	const char* pPtr = strstr(chBuf, pattern);
	int hh, mm, ss;

	if (pPtr == nullptr || sscanf(pPtr + strlen(pattern), "%02d:%02d:%02d", &hh, &mm, &ss) != 3)
		return prevValue;
	
	return hh * 3600 + mm * 60 + ss;
}

bool FfmpegRunner::runFfmpeg() const
{
	struct __stat64 buf;
	long long fileSize = 0;
	if (_wstat64(mInfile.c_str(), &buf) == 0)
		fileSize = buf.st_size;

	std::vector<wchar_t> cmdLineBuf(mCommandLine.length() + 1, L'\0');
	std::copy_n(mCommandLine.begin(), mCommandLine.length(), cmdLineBuf.begin());

	HANDLE stderrReadHandle;
	HANDLE stderrWriteHandle;
	SECURITY_ATTRIBUTES saAttr = { sizeof(SECURITY_ATTRIBUTES), nullptr, TRUE };

	if (!CreatePipe(&stderrReadHandle, &stderrWriteHandle, &saAttr, 0))		return false;
	if (!SetHandleInformation(stderrReadHandle, HANDLE_FLAG_INHERIT, 0))	return false;

	PROCESS_INFORMATION piProcInfo;
	ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));

	STARTUPINFO siStartInfo;
	ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
	siStartInfo.cb = sizeof(STARTUPINFO);
	siStartInfo.hStdError = stderrWriteHandle;
	siStartInfo.hStdOutput = nullptr;
	siStartInfo.hStdInput = nullptr;
	siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

	if (!CreateProcess(nullptr, &cmdLineBuf[0], nullptr, nullptr, TRUE, CREATE_NO_WINDOW, nullptr, mFfmpegFolder.c_str(), &siStartInfo, &piProcInfo))
		return false;

	CloseHandle(piProcInfo.hThread);

	const DWORD updIntervalMs = 100;
	unsigned processedBytes = 0, prevTime = 0, deltaProcessedBytes = 0;
	unsigned infileDurationSec = 1, currentTime = 0;

	while (WAIT_TIMEOUT == WaitForSingleObject(piProcInfo.hProcess, updIntervalMs))
	{
		DWORD dataSize;
		if (PeekNamedPipe(stderrReadHandle, nullptr, 0, nullptr, &dataSize, nullptr))
			if (dataSize > 0)
			{
				std::vector<char> buffer(dataSize + 1, 0);
				if (ReadFile(stderrReadHandle, &buffer[0], dataSize, &dataSize, nullptr))
				{
					infileDurationSec = getTimeValue(infileDurationSec, "Duration: ", buffer.data());
					currentTime = getTimeValue(currentTime, "time=", buffer.data());

					deltaProcessedBytes =  fileSize * (currentTime - prevTime) / double(infileDurationSec);
					if (processedBytes + deltaProcessedBytes > fileSize)	// to make sure we aren't over 100%
						deltaProcessedBytes = fileSize - processedBytes;

					prevTime = currentTime;
					processedBytes += deltaProcessedBytes;
				}
			}

		if (!mProcessDataProc((WCHAR*)mInfile.c_str(), deltaProcessedBytes))
			TerminateProcess(piProcInfo.hProcess, 1);
		deltaProcessedBytes = 0;
	}

	DWORD exitCode;
	GetExitCodeProcess(piProcInfo.hProcess, &exitCode);
	CloseHandle(stderrReadHandle);
	CloseHandle(stderrWriteHandle);

	return exitCode == 0 && mProcessDataProc((WCHAR*)mInfile.c_str(), fileSize - processedBytes);
}

bool FfmpegRunner::Process() const
{
	for (const auto& var_type : mSupportedTypes)
		if (ends_with(to_lower(mInfile), to_lower(L"." + to_wstring(var_type))))
			return runFfmpeg();
	return true;
}
