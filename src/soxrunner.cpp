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
	mCommandLine = quote(join_paths(mSoxFolder, std::wstring(L"sox.exe"))) + L" -S " +
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

void SoxRunner::testPercents(const char* chBuf, const char* pPtr)
{
	const char* cPtr = pPtr;
	while(*cPtr != ':')
	{
		if (cPtr == pPtr)
			return;	// not found
		cPtr--;
	}

	cPtr++;
	int result = 0;
	if (isdigit(cPtr[0]) && isdigit(cPtr[1]) && isdigit(cPtr[2]))
		result = 100;	// only 100 is 3-digit
	else if (isdigit(cPtr[0]) && isdigit(cPtr[1]))
		result = (cPtr[0] - '0') * 10 + (cPtr[1] - '0');
	else if (isdigit(cPtr[0]))
		result = cPtr[0] - '0';
	else
		return;

	std::ofstream os("testlog.txt", std::ios_base::app);
	os << result << std::endl;
}

bool SoxRunner::runSox()
{
	// cmdline must not be const for CreateProcess()
	// use "-S" first to display progress (last line: In:nn%)
	// rely on https://docs.microsoft.com/en-us/windows/win32/procthread/creating-a-child-process-with-redirected-input-and-output
	// for stderr redirection
	// also check these:
	// https://stackoverflow.com/questions/14147138/capture-output-of-spawned-process-to-string#14149200
	// https://stackoverflow.com/questions/28197891/win32-readfile-output-without-waiting-for-buffer

	std::vector<wchar_t> cmdLineBuf(mCommandLine.length() + 1, L'\0');
	std::copy_n(mCommandLine.begin(), mCommandLine.length(), cmdLineBuf.begin());

	SECURITY_ATTRIBUTES saAttr;
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;

	HANDLE g_hChildStd_ERR_Wr, g_hChildStd_ERR_Rd;// = NULL;
	CreatePipe(&g_hChildStd_ERR_Rd, &g_hChildStd_ERR_Wr, &saAttr, 0);
	SetHandleInformation(g_hChildStd_ERR_Rd, HANDLE_FLAG_INHERIT, 0);

	STARTUPINFO si;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	si.hStdError = g_hChildStd_ERR_Wr;
	si.dwFlags |= STARTF_USESTDHANDLES;

	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(pi));

	CreateProcess(NULL, &cmdLineBuf[0], NULL, NULL, false, CREATE_NO_WINDOW, NULL, mSoxFolder.c_str(), &si, &pi);

	while (WAIT_TIMEOUT == WaitForSingleObject(pi.hProcess, 200))//INFINITE);
	{
		const int BUFSIZE = 500;
		DWORD dwRead;//, dwWritten;
		//CHAR chBuf[BUFSIZE];
		BOOL tSuccess = FALSE, bSuccess = FALSE;
		DWORD avail;
		//for (;;)
		{
			tSuccess = PeekNamedPipe(g_hChildStd_ERR_Rd, NULL, 0, NULL, &avail, NULL);
			if(tSuccess)
			{
				//std::ofstream os("c:\\1\\testlog.txt", std::ios_base::app);
				//os << avail << std::endl;

				//std::vector<char> chBuf(avail);
//$mm				bSuccess = ReadFile(g_hChildStd_OUT_Rd, &chBuf[0], avail, &dwRead, NULL);
				//if (!bSuccess || dwRead == 0) break;

			}
			
			
//			if (tSuccess && avail >= BUFSIZE) {
	//			while (avail >= BUFSIZE) {
		//			//	std::string s(chBuf, dwRead);
						//out += s;
			//		avail = avail - BUFSIZE;
				//}
			//}

			//bSuccess = ReadFile(g_hChildStd_OUT_Rd, chBuf, BUFSIZE, &dwRead, NULL);
			//if (!bSuccess || dwRead == 0)
			//	break;

//			chBuf[dwRead] = 0;	// end of string
	//		const char* p2 = strrchr(chBuf, '%');
		//	if(p2 != nullptr)
			//	testPercents(chBuf, p2);
		}
	}

	DWORD exit_code;
	GetExitCodeProcess(pi.hProcess, &exit_code);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	CloseHandle(g_hChildStd_ERR_Wr);
	CloseHandle(g_hChildStd_ERR_Rd);
	//CloseHandle(g_hChildStd_OUT_Wr);

	return exit_code == 0;
}

bool SoxRunner::Process()
{
	for (const auto& var_type : mSupportedTypes)
		if (ends_with(to_lower(mInfile), to_lower(L"." + to_wstring(var_type))))
			return runSox();
	return true;
}
