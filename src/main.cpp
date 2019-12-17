#include <windows.h>
#include "wcxhead.h"
#include <cstddef>
#include <cstdio>
#include <stdlib.h>
#include "guirunner.h"
#include <wchar.h>

int* gArchive = NULL;

wcx_export HANDLE __stdcall OpenArchive(tOpenArchiveData* ArchiveData)
{
	MessageBox(NULL, L"OpenArchive called", L"ZPAQ", MB_OK | MB_ICONWARNING);

	gArchive = new int; // $MM TO FIX -- every time new archive!
	return gArchive;
}

wcx_export int __stdcall ReadHeader(HANDLE hArcData, tHeaderData* HeaderData)
{
	MessageBox(NULL, L"ReadHeader called", L"ZPAQ", MB_OK | MB_ICONWARNING);

	return E_BAD_ARCHIVE;
}

wcx_export int __stdcall ProcessFile(HANDLE hArcData, int Operation, char* DestPath, char* DestName)
{
	MessageBox(NULL, L"ProcessFile called", L"ZPAQ", MB_OK | MB_ICONWARNING);

	return E_BAD_ARCHIVE;
}

wcx_export int __stdcall CloseArchive(HANDLE hArcData) {
	MessageBox(NULL, L"CloseArchive called", L"ZPAQ", MB_OK | MB_ICONWARNING);

	return E_SMALL_BUF;
}

wcx_export void __stdcall SetChangeVolProc(HANDLE hArcData, tChangeVolProc pChangeVolProc1) {
	return;
}

tProcessDataProcW g_ProcessDataProc;



void MessageBox(char *str)
{
	if (str == NULL)
		return;
	//char *string = "The quick brown fox jumps over the lazy dog";
	size_t len = strlen(str);
	WCHAR unistring[1024];//len + 1];
	int result = MultiByteToWideChar(CP_OEMCP, 0, str, -1, unistring, len + 1);
	MessageBox(NULL, unistring, L"ZPAQ", MB_OK);
}

wcx_export void __stdcall SetProcessDataProc(HANDLE hArcData, tProcessDataProc pProcessDataProc) {
}

wcx_export void __stdcall SetProcessDataProcW(HANDLE hArcData, tProcessDataProcW pProcessDataProc) {
	char buffer[100];
	ltoa(reinterpret_cast<long>(hArcData), buffer, 10);

	MessageBox(NULL, L"SetProcessDataProc called", L"ZPAQ", MB_OK | MB_ICONWARNING);
	MessageBox(buffer);

	if (pProcessDataProc == INVALID_HANDLE_VALUE)
		MessageBox("Invalid handle");
	g_ProcessDataProc = pProcessDataProc;
	return;
}

wcx_export void __stdcall ConfigurePacker(HWND Parent, HINSTANCE DllInstance) {

	run_wx_gui_from_dll("", Parent);
}

wcx_export int __stdcall GetPackerCaps()
{
	return PK_CAPS_NEW | PK_CAPS_MULTIPLE | PK_CAPS_OPTIONS | PK_CAPS_HIDE;
}

wcx_export int __stdcall PackFiles(char* PackedFile, char* SubPath, char* SrcPath, char* AddList, int Flags)
{
	return 0;
}

wcx_export int __stdcall PackFilesW(wchar_t* PackedFile, wchar_t* SubPath, wchar_t* SrcPath, wchar_t* AddList, int Flags)
{
	MessageBox(NULL, L"PackFiles called", L"ZPAQ", MB_OK | MB_ICONWARNING);

	//MessageBox(PackedFile);
	//MessageBox(SubPath);
	//MessageBox(SrcPath);

	//MessageBox(AddList);

	//MessageBox(NULL, L"No support for Windows 9x or non-Unicode!", L"ZPAQ", MB_OK|MB_ICONWARNING);
	//foreach(var v in addList)  // convert each file

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

		//	wxThreadEvent *event =
			//	new wxThreadEvent(wxEVT_THREAD, CMD_TERMINATE);
		//	wxQueueEvent(wxApp::GetInstance(), event);



	return 0;//PACKER RESULT OK;
}