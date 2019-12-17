cd /d c:\Projects-Hg\_SharedLibs\wxWidgets_3_1_0\build\msw
"%VCINSTALLDIR%\Auxiliary\Build\vcvarsall.bat" x64
nmake /f makefile.vc TARGET_CPU=X64 RUNTIME_LIBS=static BUILD=release
nmake /f makefile.vc TARGET_CPU=X64 RUNTIME_LIBS=static
