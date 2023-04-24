#pragma once

#include "CELLApp.hpp"
#include <windows.h>
#include <tchar.h>
#include "CELLGLContext.hpp"
#include "CELLOpenGL.h"
#include "CELLFrameBigMap.h"
#include "CELLThread.hpp"
#include "CELLEvent.hpp"
#include <cassert>

namespace CELL
{
    class CELLWinApp :public CELLApp,public CELLThread
    {
    public:
        HWND            _hWnd;
        CELLGLContext   _contextGL;
		CELLContext		_context;
		CELLOpenGL		_device;
		CELLFrame*		_frame;
        CELLEvent       _set;
		bool			_threadRun;
        bool			_makeResult;
    public:
        CELLWinApp()
        {
            _hWnd		= nullptr;
			_frame		= nullptr;
			_threadRun	= true;
            _makeResult = false;
        }
    public:
        /// 创建窗口函数
        virtual bool    createWindow(int width, int height,INSTANCE hInst)
        {
            /// 1.注册窗口类
            /// 2.创建窗口
            /// 3.更新显示

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
            /// 创建窗口
            _hWnd   =   CreateWindow(
                                      _T("CELL.BigMap")
                                    , _T("BigMap")
                                    , WS_OVERLAPPEDWINDOW
                                    , CW_USEDEFAULT
                                    , 0
                                    , CW_USEDEFAULT
                                    , 0
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

			HDISPLAY    hDC = GetDC(_hWnd);
			if (!_contextGL.init(_hWnd, hDC))
			{
				DestroyWindow(_hWnd);
				return  false;
			}
            _contextGL.makeCurrentNone();

            return  true;
        }

		CELLFrame* createFrame() {
			return new CELLFrameBigMap(_context);
		}

		/**
		*   创建完成通知函数
		*/
		bool onCreate()
		{
            _makeResult = _contextGL.makeCurrent();
            assert(_makeResult);
            _set.set();
            return _makeResult;
		}
		/**
		*   线程执行函数
		*/
		bool onRun()
		{
			while (_threadRun)
			{
				render();
			}
			return  true;
		}

		/**
		*   结束函数
		*/
		virtual bool    onDestroy()
		{
			_contextGL.shutdown();
			return  false;
		}

        ///  入口函数
        virtual void    main(int argc, char** argv)
        {
			_frame = createFrame();
			if (_frame)
			{
				CELLThread::start();
                _set.wait();

                if (!_makeResult) {
                    CELLThread::join();
                    delete _frame;
                    _contextGL.shutdown();
                    return;
                }

				MSG msg = { 0 };
#if 1
				/// 主消息循环: 
				while (GetMessage(&msg, nullptr, 0, 0))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
#else
				/// 主消息循环: 
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

        /// 绘制函数
        void    render()
        {
			_frame->updateFrame(_context);
			_frame->onBeginFrame(_context);
			_frame->onEndFrame(_context);

            _contextGL.swapBuffer();
        }


        LRESULT     eventProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
        {
            switch (message)
            {
            case WM_LBUTTONDOWN:
				_frame->onLButtonDown(LOWORD(lParam), HIWORD(lParam));
                break;
            case WM_LBUTTONUP:
				_frame->onLButtonUp(LOWORD(lParam), HIWORD(lParam));
                break;
            case WM_MOUSEMOVE:
				_context._mouseX = LOWORD(lParam);
				_context._mouseY = HIWORD(lParam);
				_frame->onMouseMove(LOWORD(lParam), HIWORD(lParam));
                break;
            case WM_MOUSEWHEEL:
                break;
            case WM_PAINT:
                {
                    PAINTSTRUCT ps;
                    HDC hdc = BeginPaint(hWnd, &ps);
                    EndPaint(hWnd, &ps);
                }
                break;
            case WM_DESTROY:
				_threadRun = false;
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
                CELLWinApp*     pApp        =   (CELLWinApp*)GetWindowLongPtr(hWnd,GWL_USERDATA);
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
