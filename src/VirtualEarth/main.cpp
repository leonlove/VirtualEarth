#include "resource.h"
#include "CELLWinApp.hpp"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    CELL::CELLWinApp*  app = new CELL::CELLWinApp();


    if (!app->createWindow(800,600,hInstance))
    {
		delete app;
        return  0;
    }
    app->main(0,0);
	
	delete app;
    return  0;

}
