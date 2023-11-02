#pragma once

#include    "CELLMath.hpp"
#include	"CELLCamera.hpp"
namespace   CELL
{
    class   CELLResourceMgr;
    class   CELLOpenGL;
    class   CELLContext
    {
	public:
		CELLContext()
		{
			memset(_keyState, 0, sizeof(_keyState));
		}
    public:
        CELLOpenGL*         _device;
        /// 资源管理者指针
        CELLResourceMgr*    _resMgr;
        /// 鼠标的当前位置X
        int         _mouseX;
        /// 鼠标的当前位置Y
        int         _mouseY;
		float		_timePerFrame;
        /// 窗口的大小
        int         _width;
        int         _height;
		byte		_keyState[256];
		CELLCamera	 _camera;
		matrix4r	 _vp;
    };
}
