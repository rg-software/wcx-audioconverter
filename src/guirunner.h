#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MY_DLL_BUILDING
    #define MY_DLL_DECL __declspec(dllexport)
#else
    #define MY_DLL_DECL __declspec(dllimport)
#endif

// launch wx UI from some application that may or may not be written in wx
MY_DLL_DECL void run_wx_gui_from_dll(const char *title, HWND Parent);

// run this to shutdown running threads etc.
MY_DLL_DECL void wx_dll_cleanup();


#ifdef __cplusplus
}
#endif
