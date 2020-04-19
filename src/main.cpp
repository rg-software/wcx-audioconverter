#include <windows.h>

#ifndef WCXHEAD_INCLUDED
#define WCXHEAD_INCLUDED
#include "wcxhead.h"
#endif

#include <cstddef>
#include <string>
#include <wchar.h>
#include "settingsdialog.h"
#include "ffmpegrunner.h"
#include "inifileext.h"
#include "guirunner.h"

namespace
{
	int gArchive = 1;
	std::string gPluginIniPath;			// ini path is a std::string, all other filenames are std::wstring
	tProcessDataProcW g_ProcessDataProc;
	HWND foundFileDialogHWND;
}

HANDLE __stdcall OpenArchive(tOpenArchiveData* /*ArchiveData*/)
{
	return &gArchive;
}

int __stdcall ReadHeader(HANDLE /*hArcData*/, tHeaderData* /*HeaderData*/)
{
	return E_BAD_ARCHIVE;
}

int __stdcall ProcessFile(HANDLE /*hArcData*/, int /*Operation*/, char* /*DestPath*/, char* /*DestName*/)
{
	return E_BAD_ARCHIVE;
}

int __stdcall CloseArchive(HANDLE /*hArcData*/) 
{
	return E_SMALL_BUF;
}

void __stdcall SetChangeVolProc(HANDLE /*hArcData*/, tChangeVolProc /*pChangeVolProc1*/) 
{
}

void __stdcall SetProcessDataProc(HANDLE /*hArcData*/, tProcessDataProc /*pProcessDataProc*/) 
{
}

int __stdcall PackFiles(char* /*PackedFile*/, char* /*SubPath*/, char* /*SrcPath*/, char* /*AddList*/, int /*Flags*/)
{
	return 0;
}

// core functions
void MessageBox(char *str)	// for debugging
{
	if (str == NULL)
		return;
	size_t len = strlen(str);
	WCHAR unistring[1024];
	/*int result = */MultiByteToWideChar(CP_OEMCP, 0, str, -1, unistring, len + 1);
	MessageBox(NULL, unistring, L"Message", MB_OK);
}

void __stdcall SetProcessDataProcW(HANDLE /*hArcData*/, tProcessDataProcW pProcessDataProc) 
{
	g_ProcessDataProc = pProcessDataProc;
}

void __stdcall PackSetDefaultParams(PackDefaultParamStruct* dps)
{	
	gPluginIniPath = join_paths(get_dirname(std::string(dps->DefaultIniName)), std::string("audio-converter.ini"));

	if(GetFileAttributesA(gPluginIniPath.c_str()) == INVALID_FILE_ATTRIBUTES)
	{
		// copy from our archive
		std::string archiveIniPath = join_paths(GetModulePath(), std::string("audio-converter.ini"));
		CopyFileA(archiveIniPath.c_str(), gPluginIniPath.c_str(), FALSE);
	}
}

void __stdcall ConfigurePacker(HWND Parent, HINSTANCE /*DllInstance*/) 
{
	ShowConfigUI(gPluginIniPath, Parent);
}

int __stdcall GetPackerCaps()
{
	return PK_CAPS_NEW | PK_CAPS_MULTIPLE | PK_CAPS_OPTIONS | PK_CAPS_HIDE;
}

int _stdcall GetBackgroundFlags()
{
	return BACKGROUND_PACK | BACKGROUND_UNPACK;	// MUST be thread-safe to show correct progress indicator (due to TC bug)
}

// unfortunately, there is no good way to find a parent window for our settings screen, so let's use a hack for now
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM /*lParam*/)
{
	DWORD process;
	GetWindowThreadProcessId(hWnd, &process);

	if (GetCurrentProcessId() == process) 
	{
		wchar_t buffer[100];
		GetClassName(hWnd, buffer, 100);
		if (std::wstring(buffer) == L"TDLG2FILEACTIONMIN")
		{
			foundFileDialogHWND = hWnd;
			return FALSE;
		}
	}
	return TRUE;
}

HWND GetFileDialogHandle()
{
	foundFileDialogHWND = NULL;	// race condition possible but extremely unlikely here
	EnumWindows(EnumWindowsProc, NULL);
	return foundFileDialogHWND;
}

bool ConvertFile(wchar_t* srcPath, wchar_t* filePath, std::wstring destPath, bool savePath, bool moveFile, IniFileExt& ini)
{
	std::wstring fullFilePath = join_paths(std::wstring(srcPath), std::wstring(filePath));

	// first, skip directories (but create the same folder structure in the output directory)
	if((FILE_ATTRIBUTE_DIRECTORY & GetFileAttributes(fullFilePath.c_str())) == FILE_ATTRIBUTE_DIRECTORY)
	{
		if (savePath)
			CreateDirectory(join_paths(destPath, std::wstring(filePath)).c_str(), NULL);
		return true;	// not a file (and not an error)
	}

	std::wstring outfileRelative = savePath ? filePath : get_filename(filePath);
	std::wstring outPath = join_paths(destPath, outfileRelative);
	bool result = FfmpegRunner(srcPath, filePath, outPath, ini, g_ProcessDataProc).Process();

	if (result && moveFile)	// delete source file in case of success only
		DeleteFile(fullFilePath.c_str());

	return result;
}

bool shouldShowConfigUI()
{
	IniFileExt ini(gPluginIniPath);
	return ini.GetInteger("IsChecked", "chkAlwaysShow");
}

int __stdcall PackFilesW(wchar_t* PackedFile, wchar_t* /*SubPath*/, wchar_t* SrcPath, wchar_t* AddList, int Flags)
{
	HWND parentHwnd = GetFileDialogHandle();

	// $mm here can be problems with multithreading due to a single config file
	if (shouldShowConfigUI())
	{
		if (ShowConfigUI(gPluginIniPath, parentHwnd) == ERROR_CANCELLED)
			return 0; // no files to pack
	}

	IniFileExt ini(gPluginIniPath);

	wchar_t* curFile = AddList;
	while (*curFile)
	{
		std::wstring destPath = get_dirname(std::wstring(PackedFile));

		if (!ConvertFile(SrcPath, curFile, destPath, (Flags &  PK_PACK_SAVE_PATHS) != 0, (Flags & PK_PACK_MOVE_FILES) != 0, ini))
		{
			MessageBox(parentHwnd, (std::wstring(L"Error processing file ") + curFile).c_str(), L"Audioconverter error", MB_ICONERROR);
			return E_EABORTED;
		}

		curFile += wcslen(curFile) + 1;
	}
	return 0;
}
