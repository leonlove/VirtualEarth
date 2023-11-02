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
        /// ��Դ������ָ��
        CELLResourceMgr*    _resMgr;
        /// ���ĵ�ǰλ��X
        int         _mouseX;
        /// ���ĵ�ǰλ��Y
        int         _mouseY;
		float		_timePerFrame;
        /// ���ڵĴ�С
        int         _width;
        int         _height;
		byte		_keyState[256];
		CELLCamera	 _camera;
		matrix4r	 _vp;
    };
}
