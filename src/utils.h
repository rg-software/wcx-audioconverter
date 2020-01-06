#pragma once
#include <string>
#include <vector>

// $mm TODO: make sure these string <-> wstring functions work correctly with non-Latin characters

inline std::string to_string(const std::wstring& s)
{
	std::vector<char> result(s.length() + 1);
	wcstombs(&result[0], s.c_str(), s.length());
	return std::string(&result[0]);
}

inline std::wstring to_wstring(const std::string& s)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &s[0], (int)s.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &s[0], (int)s.size(), &wstrTo[0], size_needed);
	
	return wstrTo;
}

template<typename T> std::basic_string<T> to_lower(const std::basic_string<T>& s)
{
	std::basic_string<T> result;
	std::transform(s.begin(), s.end(), std::back_inserter(result), ::tolower);
	return result;
}

template<typename T> bool ends_with(const std::basic_string<T>& s, const std::basic_string<T>& tail)
{
	return s.substr(s.length() - tail.length()) == tail;
}

inline std::wstring change_extension(const std::wstring& path, const std::wstring& ext)
{
	return path.substr(0, path.find_last_of(L'.') + 1) + ext;
}

inline std::wstring quote(const std::wstring& s)
{
	return L"\"" + s + L"\"";
}

inline std::wstring get_filename(const std::wstring& path)
{
	return path.substr(path.find_last_of(L'\\') + 1);
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

inline bool file_exists(const std::wstring& path)
{
	struct __stat64 buf;
	return _wstat64(path.c_str(), &buf) == 0;
}