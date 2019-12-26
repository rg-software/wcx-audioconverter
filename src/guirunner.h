#pragma once
#include <string>
#include <minwindef.h>
#include <wincon.h>

std::string GetModulePath();
DWORD ShowConfigUI(const char* iniPath, HWND Parent);
