#pragma once

#include "CELLPlatform.hpp"
#include "CELLFrame.hpp"

namespace CELL
{
    class   CELLApp
    {
    public:

        /// �������ں���
        virtual bool        createWindow(int width,int height,INSTANCE hInst)  =   0;
        /// <summary>
        /// �������
        /// </summary>
        virtual CELLFrame*  createFrame()   =   0;
        ///  ��ں���
        virtual void        main(int argc,char** argv)  =   0;
    };
}
