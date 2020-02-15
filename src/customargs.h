#pragma once
#include "inifileext.h"

class FfmpegRunner;
void AddCustomArgsGlobal(FfmpegRunner& fr, IniFileExt& ini);
std::wstring AddCustomArgsMP3(FfmpegRunner& fr, IniFileExt& ini);
std::wstring AddCustomArgsOGG(FfmpegRunner& fr, IniFileExt& ini);
