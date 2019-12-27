#pragma once
#include <string>
#include "inifileext.h"
#include "guirunner.h"
#include "utils.h"

class SoxRunner
{
public:
	SoxRunner(std::wstring& infile, std::wstring& outfile, IniFileExt& ini)
		: mSoxPath(GetModulePath() + L"Sox")
	{
		mInfile = infile;
		mOutfile = outfile;
		mSupportedTypes = ini.GetStringList("fileTypes");
		mChannels = ini.GetInteger("isStereo") ? 2 : 1;
		mSampleRate = ini.GetStringItem("sampleRates", "sampleRate");

		if (ini.GetInteger("isNormalize"))
			mCustomArgs += " --norm";

		addCustomSettings(ini);
	}

	void Process()
	{
		for (const auto& var_type : mSupportedTypes)
			if(ends_with(to_lower(mInfile), to_lower(L"." + to_wstring(var_type))))
			{
				// cmdline must not be const for CreateProcess()
				std::wstring soxLine = join_paths(mSoxPath, L"sox.exe");
				std::wstring cmdLine = quote(soxLine) + L" " + quote(mInfile) + L" " + to_wstring(mCustomArgs) + L" " + quote(mOutfile);
//				MessageBox(NULL, cmdLine.c_str(), L"Message", MB_OK);

				std::vector<wchar_t> cmdLineBuf(cmdLine.length() + 1);
				std::fill_n(cmdLineBuf.begin(), cmdLine.length() + 1, L'\0');
				std::copy_n(cmdLine.begin(), cmdLine.length(), cmdLineBuf.begin());

				STARTUPINFO si;
				PROCESS_INFORMATION pi;
				ZeroMemory(&si, sizeof(si));
				si.cb = sizeof(si);
				ZeroMemory(&pi, sizeof(pi));

				CreateProcess(soxLine.c_str(), &cmdLineBuf[0], NULL, NULL, false,
								CREATE_NO_WINDOW, NULL, mSoxPath.c_str(), &si, &pi);

				WaitForSingleObject(pi.hProcess, INFINITE);
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
				
				//	SoxObject.OnProgress += Sox_OnProgress;
				//	SoxObject.Process(Infile, Outfile);
				break;
			}
	}

private:
	void addCustomSettings(IniFileExt& ini)
	{
		// currently we only support MP3
		if (ini.GetStringItem("fileTypes", "fileType") == std::string("MP3"))
		{
			mCustomArgs += " --channels " + std::to_string(mChannels);

			if (ini.GetStringItem("mp3Modes", "mp3Mode") == std::string("CBR")) // set bitrate ("128", "256")
				mCustomArgs += " -C " + ini.GetStringItem("mp3CbrBitrates", "mp3CbrBitrate");
			else // VBR: set quality as -0..-9	// $mm TODO: double check!
				mCustomArgs += " -C -" + std::to_string(ini.GetInteger("mp3VbrQuality") * 2);
		}
	}

	std::wstring mSoxPath;
	std::wstring mInfile, mOutfile;
	int mChannels;
	std::string mSampleRate;
	std::vector<std::string> mSupportedTypes;
	std::string mCustomArgs;
/*
	private Sox SoxObject;
	private string Infile, Outfile;
	private string[] SupporedTypes;

	public int Progress{ get; private set; }
	public bool Done{ get; private set; }


	public void Process()
	{
		foreach(var type in SupporedTypes)     // skip unsupported file types
			if (Infile.ToUpper().EndsWith("." + type))
			{
				SoxObject.OnProgress += Sox_OnProgress;
				SoxObject.Process(Infile, Outfile);
				break;
			}

		Done = true;
	}

	private void Sox_OnProgress(object sender, ProgressEventArgs e)
	{
		Progress = e.Progress;
	}

	public void Abort()
	{
		SoxObject.Abort();
	}
	*/

};