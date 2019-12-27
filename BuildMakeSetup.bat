:: This script creates a release (setup) package using a prebuilt project.
@echo off
setlocal

call "%VCINSTALLDIR%\Auxiliary\Build\vcvarsall.bat" x86
msbuild Audioconverter.sln /t:Build /p:Configuration=Release;Platform=Win32;UseEnv=true

call "%VCINSTALLDIR%\Auxiliary\Build\vcvarsall.bat" x64
msbuild Audioconverter.sln /t:Build /p:Configuration=Release;Platform=x64;UseEnv=true

del /Q audioconverter.zip
rmdir /S /Q ReleaseWCX

mkdir ReleaseWCX
mkdir ReleaseWCX\sox

copy sox-14.4.2\*.* ReleaseWCX\sox\
copy vc_mswu_x64\my_dll.dll ReleaseWCX\audioconverter.wcx64
copy vc_mswu\my_dll.dll ReleaseWCX\audioconverter.wcx
copy audioconverter.ini ReleaseWCX\
copy pluginst.inf ReleaseWCX\
copy Readme.md ReleaseWCX\
copy Screenshot.png ReleaseWCX\

powershell.exe -nologo -noprofile -command "& { Add-Type -A 'System.IO.Compression.FileSystem'; [IO.Compression.ZipFile]::CreateFromDirectory('ReleaseWCX', 'audioconverter.zip'); }"
echo Resulting file audioconverter.zip created!