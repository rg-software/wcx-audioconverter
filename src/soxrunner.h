#pragma once
#include <string>
class SoxRunner
{
public:
	//SoxRunner(std::string& infile, std::string& outfile)	// 

/*
	private Sox SoxObject;
	private string Infile, Outfile;
	private string[] SupporedTypes;

	public int Progress{ get; private set; }
	public bool Done{ get; private set; }

		public SoxRunner(string infile, string outfile, SettingsDialog sd)
	{
		string soxPath = AppDomain.CurrentDomain.BaseDirectory + Path.DirectorySeparatorChar + "Sox" + Path.DirectorySeparatorChar + "sox.exe";

		SoxObject = new Sox(soxPath);
		Infile = infile;
		Outfile = outfile;
		Done = false;
		Progress = 0;

		// set global (format-independent) parameters
		SupporedTypes = sd.SupportedTypes;
		SoxObject.Output.SampleRate = sd.GetSamplingRate();
		SoxObject.Output.Channels = sd.GetChannels();

		if (sd.GetNormalize())
			SoxObject.CustomArgs += " --norm";

		// apply format-specific settings
		AddCustomSettings(sd);
	}

	void AddCustomSettings(SettingsDialog sd)
	{
		// currently we only support MP3
		if (sd.GetOutputType().Equals("MP3"))
		{
			if (sd.GetMp3Mode().Equals("CBR")) // set bitrate ("128", "256")
				SoxObject.Output.CustomArgs += " -C " + sd.GetMp3CbrBitrate();
			else // VBR: set quality as -0..-9
				SoxObject.Output.CustomArgs += " -C -" + sd.GetMp3VbrQuality();
		}
	}

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