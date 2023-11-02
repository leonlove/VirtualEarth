#pragma once

#include    "CELLApp.hpp"
#include    <windows.h>
#include    <tchar.h>
#include    "CELLGLContext.hpp"
#include    "CELLOpenGL.h"
#include    "CELLFrameBigMap.h"
#include    "CELLContext.hpp"
#include    "CELLThread.hpp"
#include    "CELLEvent.hpp"
#include    "CELLProgramLibary.hpp"
#include    "CELLResourceMgr.hpp"
#include    <assert.h>


namespace CELL
{
    class CELLWinApp 
        :public CELLApp
        ,public CELLThread
    {
    public:
        HWND            _hWnd;
        CELLGLContext   _contextGL;
        CELLContext     _context;
        CELLResourceMgr _resMgr;
        CELLOpenGL      _device;
        CELLFrame*      _frame;
        bool            _threadRun;
        bool            _makeReuslt;
        CELLEvent       _event;
    public:
        CELLWinApp()
        {
            _hWnd               =   0;
            _frame              =   0;
            _threadRun          =   true;
            _makeReuslt         =   false;
            _context._device    =   &_device;
            _context._resMgr    =   &_resMgr;
        }
    public:
        /// �������ں���
        virtual bool    createWindow(int width, int height,INSTANCE hInst)
        {
            /// 1.ע�ᴰ����
            /// 2.��������
            /// 3.������ʾ

            WNDCLASSEXW wcex;

            wcex.cbSize         =   sizeof(WNDCLASSEX);

            wcex.style          =   CS_HREDRAW | CS_VREDRAW;
            wcex.lpfnWndProc    =   wndProc;
            wcex.cbClsExtra     =   0;
            wcex.cbWndExtra     =   0;
            wcex.hInstance      =   hInst;
            wcex.hIcon          =   0;
            wcex.hCursor        =   LoadCursor(nullptr, IDC_ARROW);
            wcex.hbrBackground  =   (HBRUSH)(COLOR_WINDOW + 1);
            wcex.lpszMenuName   =   0;
            wcex.lpszClassName  =   _T("CELL.BigMap");
            wcex.hIconSm        =   0;
            RegisterClassExW(&wcex);
            /// ��������
            _hWnd   =   CreateWindow(
                                      _T("CELL.BigMap")
                                    , _T("BigMap")
                                    , WS_OVERLAPPEDWINDOW
                                    , CW_USEDEFAULT
                                    , 0
                                    , width
                                    , height
                                    , nullptr
                                    , nullptr
                                    , hInst
                                    , this);
            if (_hWnd == 0 )
            {
                return  false;
            }

            ShowWindow(_hWnd,SW_SHOW);
            UpdateWindow(_hWnd);

            HDISPLAY    hDC     =   GetDC(_hWnd);
            if(!_contextGL.init(_hWnd,hDC))
            {
                DestroyWindow(_hWnd);
                return  false;
            }
            _device.initialize();
            _context._resMgr->initialize(_context._device);
            /// ��������̵߳İ�
            _contextGL.makeCurrentNone();
            return  true;
        }

        /// <summary>
        /// �������
        /// </summary>
        virtual CELLFrame*  createFrame()
        {
            if (IsWindow(_hWnd))
            {
                RECT    rect;
                GetClientRect(_hWnd, &rect);
                _context._width     =   rect.right - rect.left;
                _context._height    =   rect.bottom - rect.top;
            }
            else
            {
                _context._width     =   64;
                _context._height    =   64;
            }
            return  new CELLFrameBigMap(_context);
        }
        ///  ��ں���
        virtual void    main(int argc, char** argv)
        {

            _frame  =   createFrame();

            if (_frame != 0)
            {
                CELLThread::start();

                _event.wait();
                if (!_makeReuslt)
                {
                    CELLThread::join();
                    delete  _frame;
                    _contextGL.shutdown();
                    return;
                }
                MSG msg = { 0 };
#if 1
                /// ����Ϣѭ��: 
                /// PeekMessage
                while (GetMessage(&msg, nullptr, 0, 0))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
#else
                /// ����Ϣѭ��: 
                /// PeekMessage
                while (msg.message != WM_QUIT)
                {
                    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
                    {
                        TranslateMessage(&msg);
                        DispatchMessage(&msg);
                    }
                    render();
                }
                _contextGL.shutdown();
#endif
            }
            
        }

        /// ���ƺ���
        virtual void    render()
        {
            if (_frame == 0)
            {
                return;
            }
            _frame->update(_context);
            _frame->onFrameStart(_context);
            _frame->onFrameEnd(_context);
            _contextGL.swapBuffer();
        }
        //////////////////////////////////////////////////////////////////////////

        /// <summary>
        /// �������֪ͨ����
        /// </summary>
        virtual bool    onCreate()
        {
            _makeReuslt =   _contextGL.makeCurrent();
            assert(_makeReuslt);
            _event.set();
            return  _makeReuslt;
        }
     
        /// <summary>
        /// �߳�ִ�к���
        /// </summary>
        virtual bool    onRun()
        {
            while (_threadRun)
            {
                render();
            }
            return  false;
        }
        /// <summary>
        /// ��������
        /// </summary>
        virtual bool    onDestroy()
        {
            _contextGL.shutdown();
            return  false;
        }

    protected:
        LRESULT         eventProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
        {
            switch (message)
            {
            case WM_LBUTTONDOWN:
                _frame->onLButtonDown(LOWORD(lParam),HIWORD(lParam));
                break;
            case WM_LBUTTONUP:
                _frame->onLButtonUp(LOWORD(lParam),HIWORD(lParam));
                break;
            case WM_MOUSEMOVE:
                _context._mouseX = LOWORD(lParam);
                _context._mouseY = HIWORD(lParam);
                _frame->onMouseMove(LOWORD(lParam), HIWORD(lParam));
                break;
            case WM_MOUSEWHEEL:
				_frame->onMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam));
                break;
			case WM_KEYDOWN:
				_frame->onKeyDown(wParam);
				break;
			case WM_KEYUP:
				_frame->onKeyUp(wParam);
				break;
            case WM_PAINT:
                {
                    PAINTSTRUCT ps;
                    HDC hdc = BeginPaint(hWnd, &ps);
                    EndPaint(hWnd, &ps);
                }
                break;
            case WM_SIZE:
                {
                    if(IsWindow(_hWnd))
                    { 
                        RECT    rect;
                        GetClientRect(_hWnd,&rect);
                        _context._width     =   rect.right - rect.left;
                        _context._height    =   rect.bottom - rect.top;
                    }
                }
                break;
            case WM_DESTROY:
                _threadRun  =   false;
                CELLThread::join();
                PostQuitMessage(0);
                break;
            default:
                return  DefWindowProc(hWnd, message, wParam, lParam);
            }
            return  S_OK;
        }

    protected:
        static  LRESULT CALLBACK  wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
        {
            if (WM_CREATE == message)
            {
                CREATESTRUCT*   pSTRUCT     =   (CREATESTRUCT* )lParam;
                CELLWinApp*     pApp        =   (CELLWinApp*)pSTRUCT->lpCreateParams;
                #ifndef GWL_USERDATA
                #define GWL_USERDATA (-21)
                #endif
                SetWindowLongPtr(hWnd,GWL_USERDATA,(LONG_PTR)pApp);
                return  pApp->eventProc(hWnd,WM_CREATE,wParam,lParam);
            }
            else
            {
                CELLWinApp*     pApp        =       (CELLWinApp*)GetWindowLongPtr(hWnd,GWL_USERDATA);
                if (pApp)
                {
                    return  pApp->eventProc(hWnd,message,wParam,lParam);
                }
                else
                {
                    return DefWindowProc(hWnd, message, wParam, lParam);
                }
            }
        }
    };

}
