#pragma once
#include <string>
#include "inifileext.h"

std::string GetModulePath();

class SoxRunner
{
public:
	SoxRunner(std::wstring& infile, std::wstring& outfile, IniFileExt& ini)
		: mSoxPath(GetModulePath() + "Sox\\sox.exe")
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

		size_t len = strlen(mCustomArgs.c_str());
		WCHAR cust_args[1024];
		int result = MultiByteToWideChar(CP_OEMCP, 0, mCustomArgs.c_str(), -1, cust_args, len + 1);


		//for (const auto& var_type : mSupportedTypes)
		{
			std::wstring msg = mInfile + L" " + mOutfile + L" " + std::wstring(cust_args);
			MessageBox(NULL, msg.c_str(), L"Message", MB_OK);

		}
		//	if (Infile.ToUpper().EndsWith("." + type)) // $mm TO RETURN
			//{
			//	SoxObject.OnProgress += Sox_OnProgress;
			//	SoxObject.Process(Infile, Outfile);
			//	break;
			//}
	}

private:
	void addCustomSettings(IniFileExt& ini)
	{
		// currently we only support MP3
		if (ini.GetStringItem("fileTypes", "fileType") == std::string("MP3"))
		{
			if (ini.GetStringItem("mp3Modes", "mp3Mode") == std::string("CBR")) // set bitrate ("128", "256")
				mCustomArgs += " -C " + ini.GetStringItem("mp3CbrBitrates", "mp3CbrBitrate");
			else // VBR: set quality as -0..-9	// $mm TODO: double check!
				mCustomArgs += " -C -" + std::to_string(ini.GetInteger("mp3VbrQuality") * 2);
		}
	}

	std::string mSoxPath;
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