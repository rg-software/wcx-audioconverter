#pragma once
#include <string>
#include <minwindef.h>

std::string GetModulePath();
DWORD ShowConfigUI(const std::string& iniPath, HWND Parent);
