#include <windows.h>
#include "wcxhead.h"
#include <cstddef>
#include <cstdio>
#include <string>
#include <wchar.h>
#include "settingsdialog.h"
#include "soxrunner.h"
#include "inifileext.h"
#include "guirunner.h"

namespace
{
	int gArchive = 1;
	std::wstring gPluginIniPath;
	tProcessDataProcW g_ProcessDataProc;
	HWND foundFileDialogHWND;
}

wcx_export HANDLE __stdcall OpenArchive(tOpenArchiveData* ArchiveData)
{
	return &gArchive;
}

wcx_export int __stdcall ReadHeader(HANDLE hArcData, tHeaderData* HeaderData)
{
	return E_BAD_ARCHIVE;
}

wcx_export int __stdcall ProcessFile(HANDLE hArcData, int Operation, char* DestPath, char* DestName)
{
	return E_BAD_ARCHIVE;
}

wcx_export int __stdcall CloseArchive(HANDLE hArcData) 
{
	return E_SMALL_BUF;
}

wcx_export void __stdcall SetChangeVolProc(HANDLE hArcData, tChangeVolProc pChangeVolProc1) 
{
}

wcx_export void __stdcall SetProcessDataProc(HANDLE hArcData, tProcessDataProc pProcessDataProc) 
{
}

wcx_export int __stdcall PackFiles(char* PackedFile, char* SubPath, char* SrcPath, char* AddList, int Flags)
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
	int result = MultiByteToWideChar(CP_OEMCP, 0, str, -1, unistring, len + 1);
	MessageBox(NULL, unistring, L"Message", MB_OK);
}

wcx_export void __stdcall SetProcessDataProcW(HANDLE hArcData, tProcessDataProcW pProcessDataProc) 
{
	g_ProcessDataProc = pProcessDataProc;
}

wcx_export void __stdcall PackSetDefaultParams(PackDefaultParamStruct* dps)
{	
	gPluginIniPath = GetModulePath() + L"audioconverter.ini";
}

wcx_export void __stdcall ConfigurePacker(HWND Parent, HINSTANCE DllInstance) 
{
	ShowConfigUI(gPluginIniPath, Parent);
}

wcx_export int __stdcall GetPackerCaps()
{
	return PK_CAPS_NEW | PK_CAPS_MULTIPLE | PK_CAPS_OPTIONS | PK_CAPS_HIDE;
}

wcx_export int _stdcall GetBackgroundFlags()
{
	return BACKGROUND_PACK | BACKGROUND_UNPACK;	// MUST be thread-safe to show correct progress indicator (due to TC bug)
}

// unfortunately, there is no good way to find a parent window for our settings screen, so let's use a hack for now
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
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

bool ConvertFile(const std::wstring& srcPath, const std::wstring& filePath, const std::wstring& destPath, bool savePath, bool moveFile, IniFileExt& ini)
{
	std::wstring fullFilePath = join_paths(srcPath, filePath);

	// first, skip directories (but create the same folder structure in the output directory)
	if((FILE_ATTRIBUTE_DIRECTORY & GetFileAttributes(fullFilePath.c_str())) == FILE_ATTRIBUTE_DIRECTORY)
	{
		if (savePath)
			CreateDirectory(join_paths(destPath, filePath).c_str(), NULL);
		return true;	// not a file
	}

	// prepare full input and output file names
	//var fileSize = (int)new System.IO.FileInfo(fullFilePath).Length;

	// use: changeExtension, getFilename
	std::wstring outExtension = to_wstring(to_lower(ini.GetStringItem("fileTypes", "filetype")));
	std::wstring outfileRelative = savePath ? filePath : get_filename(filePath);
	std::wstring outfile = join_paths(destPath, change_extension(outfileRelative, outExtension));

	SoxRunner sr(fullFilePath, outfile, ini);

	// $mm TODO: make it run in a background thread and update progress indicator periodically
	sr.Process();

/*	
	// run Sox
	var sr = new SoxRunner(fullFilePath, outfile, sd);
	Thread caller = new Thread(new ThreadStart(sr.Process));
	caller.Start();

	// update progress bar until the process is finished
	var prevProgress = 0;
	while (!sr.Done)
	{
		Thread.Sleep(100);
		var progress = (sr.Progress - prevProgress)*fileSize*0.01f;
		prevProgress = sr.Progress;

		if (ProcessDataProc(filePath, (int)progress) == 0)
		{
			sr.Abort();
			return false;
		}
	}

	*/
	if (moveFile)
		DeleteFile(fullFilePath.c_str());

	return true;
}

wcx_export int __stdcall PackFilesW(wchar_t* PackedFile, wchar_t* SubPath, wchar_t* SrcPath, wchar_t* AddList, int Flags)
{
	HWND parentHwnd = GetFileDialogHandle();

	IniFileExt ini(to_string(gPluginIniPath));

	if (ini.GetInteger("alwaysShow"))
	{
		if (ShowConfigUI(gPluginIniPath, parentHwnd) == ERROR_CANCELLED)
			return 0; // no files to pack
	}

	wchar_t* curFile = AddList;
	while (*curFile)
	{
		std::wstring destPath = get_dirname(PackedFile);

		if (!ConvertFile(SrcPath, curFile, destPath, (Flags &  PK_PACK_SAVE_PATHS) != 0, (Flags & PK_PACK_MOVE_FILES) != 0, ini))
			return E_EABORTED;

		/*
		std::wstring fullFilePath = std::wstring(SrcPath) + curFile;
		MessageBox(NULL, fullFilePath.c_str(), L"", 0);

		struct __stat64 buf;
		int size = 0;
		if (_wstat64(fullFilePath.c_str(), &buf) == 0)
			size = buf.st_size;//MessageBox("File not found");//return -1; // error, could use errno to find out more

		g_ProcessDataProc(curFile, size);
		*/
		curFile += wcslen(curFile) + 1;
	}
	return 0;
}
