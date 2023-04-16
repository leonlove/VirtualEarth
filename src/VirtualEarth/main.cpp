#include "resource.h"
#include "CELLWinApp.hpp"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    CELL::CELLWinApp  app;


    if (!app.createWindow(800,600,hInstance))
    {
        return  0;
    }
    app.main(0,0);

    return  0;

}
