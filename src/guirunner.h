#pragma once
#include <string>
#include <minwindef.h>

std::wstring GetModulePath();
DWORD ShowConfigUI(const std::wstring& iniPath, HWND Parent);
