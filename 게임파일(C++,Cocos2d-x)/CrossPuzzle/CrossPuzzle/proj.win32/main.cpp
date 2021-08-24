#include "stdafx.h"
#include "main.h"
#include <crtdbg.h>

USING_NS_CC;

// uncomment below line, open debug console
//#define USE_WIN32_CONSOLE
//
//#ifdef _DEBUG || DEBUG
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
//#endif

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	srand(time(NULL));
//#ifdef USE_WIN32_CONSOLE
//    AllocConsole();
//    freopen("CONIN$", "r", stdin);
//    freopen("CONOUT$", "w", stdout);
//    freopen("CONOUT$", "w", stderr);
//#endif

    // create the application instance
    AppDelegate app;
    CCEGLView& eglView = CCEGLView::sharedOpenGLView();


    eglView.setViewName("CrossPuzzle");
    eglView.setFrameSize(480 * 0.9f, 800 * 0.9f);
    // set the design resolution screen size, if you want to use Design Resoulution scaled to current screen, please uncomment next line.
   eglView.setDesignResolutionSize(480, 800);
	
   // eglView.setFrameSize(720 * 0.5f, 1280 * 0.5f);
    // set the design resolution screen size, if you want to use Design Resoulution scaled to current screen, please uncomment next line.
    //eglView.setDesignResolutionSize(720, 1280);

    int ret = CCApplication::sharedApplication().run();

#ifdef USE_WIN32_CONSOLE
    FreeConsole();
#endif

    return ret;
}
