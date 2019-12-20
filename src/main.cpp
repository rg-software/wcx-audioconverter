#include <windows.h>
#include "wcxhead.h"
#include <cstddef>
#include <cstdio>
#include <string>
#include <wchar.h>
#include "settingsdialog.h"
#include <fstream>

int gArchive = 1;
std::string gPluginIniPath;

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

tProcessDataProcW g_ProcessDataProc;
DWORD ShowConfigUI(const char* iniPath, HWND Parent);

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
	gPluginIniPath = dps->DefaultIniName;
	gPluginIniPath = gPluginIniPath.substr(0, gPluginIniPath.find_last_of('\\') + 1) + "audioconverter.ini";
}

wcx_export void __stdcall ConfigurePacker(HWND Parent, HINSTANCE DllInstance) 
{
	ShowConfigUI(gPluginIniPath.c_str(), Parent);
}

wcx_export int __stdcall GetPackerCaps()
{
	return PK_CAPS_NEW | PK_CAPS_MULTIPLE | PK_CAPS_OPTIONS | PK_CAPS_HIDE;
}

wcx_export int _stdcall GetBackgroundFlags()
{
	return BACKGROUND_PACK | BACKGROUND_UNPACK;	// MUST be thread-safe to show correct progress indicator (due to TC bug)
}

// this is a quick check function, necessary due to the fact that 
// wxFileConfig and SettingsDialog cannot be used here (outside wxWidgets)
bool alwaysShow()
{
	std::ifstream is(gPluginIniPath);
	std::string asLine = "alwaysShow=1";
	std::string line;
	while (std::getline(is, line))
		if (line.substr(0, asLine.length()) == asLine)
			return true;
	return false;
}

wcx_export int __stdcall PackFilesW(wchar_t* PackedFile, wchar_t* SubPath, wchar_t* SrcPath, wchar_t* AddList, int Flags)
{
	if (alwaysShow()) // $MM TODO: get parent HWND of TotalCommander and use it instead of NULL
	{
		if (ShowConfigUI(gPluginIniPath.c_str(), NULL) == ERROR_CANCELLED)	
			return 0; // no files to pack
	}

//	foreach(var v in addList)  // convert each file
	//{
		//if (!ConvertFile(srcPath, v, destPath, (flags & PackFilesFlags.SavePaths) != 0, (flags & PackFilesFlags.MoveFiles) != 0, sd))
			//return PackerResult.EAborted;
//	}

	return 0;


	//std::wostream wos(PackedFile);
	auto fhandle = _wfopen(PackedFile, L"wb");
	fprintf(fhandle, "blablablabla");
	fclose(fhandle);

	wchar_t* CurFile = AddList;
	int FilesCount = 0;
	while (*CurFile)
	{
		//	MessageBox("File found");
			//MessageBox(CurFile);
		CurFile += wcslen(CurFile) + 1;
		FilesCount++;
	}

	CurFile = AddList;
	//int progress = 0;
	for (size_t f = 1; f <= FilesCount + 1; ++f)
	{
		//MessageBox("Packing file");
		//MessageBox(CurFile);


		struct __stat64 buf;
		int size = 0;
		if (_wstat64(CurFile, &buf) == 0)
			size = buf.st_size;//MessageBox("File not found");//return -1; // error, could use errno to find out more

		//return buf.st_size;
		//int size = buf.st_size;

		g_ProcessDataProc(CurFile, size);//-(100 * f / FilesCount));
		CurFile += wcslen(CurFile) + 1;
		Sleep(1000);
	}

	/*	std::vector<std::string> files = { "temp1.txt", "temp2.txt", "temp3.txt", "temp4.txt" };
		for (size_t f = 1; f <= files.size(); ++f)
		{
			g_ProcessDataProc((char*)files[f-1].c_str(), -(100*f/files.size()));
			for(size_t i = 0; i < 10; ++i)
			{
				g_ProcessDataProc((char*)files[f-1].c_str(), -i*10 - 1000);
				Sleep(100);
			}
		}*/
}

/*
private bool ConvertFile(string srcPath, string filePath, string destPath, bool savePath, bool moveFile, SettingsDialog sd)
{
	// first, skip directories (but create the same folder structure in the output directory)
	var fullFilePath = srcPath + Path.DirectorySeparatorChar + filePath;
	FileAttributes attr = File.GetAttributes(fullFilePath);
	if ((attr & FileAttributes.Directory) == FileAttributes.Directory)
	{
		if (savePath)
			System.IO.Directory.CreateDirectory(destPath + Path.DirectorySeparatorChar + filePath);
		return true; // not a file
	}


	// prepare full input and output file names
	var fileSize = (int)new System.IO.FileInfo(fullFilePath).Length;
	string outExtension = "." + sd.GetOutputType().ToLower();
	string outfileRelative = savePath ? filePath : Path.GetFileName(filePath);
	string outfile = destPath + Path.DirectorySeparatorChar + Path.ChangeExtension(outfileRelative, outExtension);

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

	if (moveFile)
		System.IO.File.Delete(fullFilePath);

	return true;
}
*/