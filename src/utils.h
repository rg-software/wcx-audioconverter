#pragma once
#include <string>
#include <vector>

inline std::string to_string(const std::wstring& s)
{
	std::vector<char> result(s.length() + 1);
	wcstombs(&result[0], s.c_str(), s.length());
	return std::string(&result[0]);
}

inline std::wstring to_wstring(const std::string& s)
{
	return std::wstring(s.begin(), s.end());
}

inline std::string to_lower(const std::string& s)
{
	std::string result;
	std::transform(s.begin(), s.end(), std::back_inserter(result), ::tolower);
	return result;
}

inline std::wstring change_extension(const std::wstring& path, const std::wstring& ext)
{
	return path.substr(0, path.find_last_of(L'.') + 1) + ext;
}

inline std::wstring get_filename(const std::wstring& path)
{
	return path.substr(path.find_last_of(L'\\' + 1));
}

inline std::wstring get_dirname(const std::wstring& path)
{
	return path.substr(0, path.find_last_of(L'\\'));	// return without trailing backslash
}

inline std::wstring join_paths(const std::wstring& p1, const std::wstring& p2)
{
	std::wstring sep = p1.back() == L'\\' ? L"" : L"\\";

	return p1 + sep + p2;
}