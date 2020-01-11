#pragma once
#include <string>
#include <vector>

inline std::wstring to_wstring(const std::string& s)
{
	auto size = MultiByteToWideChar(CP_UTF8, 0, &s[0], (int)s.size(), NULL, 0);	// should be ASCII anyway
	std::wstring result(size, 0);
	MultiByteToWideChar(CP_UTF8, 0, &s[0], (int)s.size(), &result[0], size);
	
	return result;
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

template<typename CharT> std::basic_string<CharT> get_dirname(const std::basic_string<CharT>& path)
{
	return path.substr(0, path.find_last_of(static_cast<CharT>('\\')));	// return without trailing backslash
}

template<typename CharT> std::basic_string<CharT> join_paths(const std::basic_string<CharT>& p1, const std::basic_string<CharT>& p2)
{
	CharT sepChar = static_cast<CharT>('\\');
	std::basic_string<CharT> sepStr;
	if(p1.back() != sepChar)
		sepStr += sepChar;

	return p1 + sepStr + p2;
}
