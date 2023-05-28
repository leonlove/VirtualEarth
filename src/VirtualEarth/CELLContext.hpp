#pragma once

#include    "CELLMath.hpp"
namespace   CELL
{
    class   CELLResourceMgr;
    class   CELLOpenGL;
    class   CELLContext
    {
    public:
        CELLOpenGL*         _device;
        /// ��Դ������ָ��
        CELLResourceMgr*    _resMgr;
        /// ���ĵ�ǰλ��X
        int         _mouseX;
        /// ���ĵ�ǰλ��Y
        int         _mouseY;

        /// ���ڵĴ�С
        int         _width;
        int         _height;
        /// 2d ��ĻͶӰ����
        matrix4r    _screenPrj;

    };
}
