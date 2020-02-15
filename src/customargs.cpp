#include "customargs.h"
#include "ffmpegrunner.h"

void AddCustomArgsGlobal(FfmpegRunner& fr, IniFileExt& ini)
{
	fr.AddCustomArgument("-ar", ini.GetStringItem("Items", "Selection", "cbSamplingRate"));
	fr.AddCustomArgument("-ac", ini.GetInteger("IsChecked", "chkStereo") ? 2 : 1);

}
std::wstring AddCustomArgsMP3(FfmpegRunner& fr, IniFileExt& ini)
{
	fr.AddCustomArgument("-codec:a", "libmp3lame");

	if (ini.GetInteger("IsChecked", "cbMp3Cbr"))
		fr.AddCustomArgument("-b:a", ini.GetStringItem("Items", "Selection", "cbMp3CbrRates"));
	else // for VBR
		fr.AddCustomArgument("-qscale:a", ini.GetStringItem("QValues", "Selection", "cbMp3VbrQuality")); // range is 0-9 where a lower value is a higher quality

	return L"mp3";

}

std::wstring AddCustomArgsOGG(FfmpegRunner& fr, IniFileExt& ini)
{
	fr.AddCustomArgument("-codec:a", "libvorbis");

	if (ini.GetInteger("IsChecked", "cbOggAbr"))
		fr.AddCustomArgument("-b:a", ini.GetStringItem("Items", "Selection", "cbOggAbrRates"));
	else // for VBR
		fr.AddCustomArgument("-qscale:a", ini.GetStringItem("QValues", "Selection", "cbOggVbrQuality"));	// range is -1 to 10, where 10 is the best quality; default/average is 3.0

	return L"ogg";
}
