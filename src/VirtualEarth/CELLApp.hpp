#pragma once

#include "CELLPlatform.hpp"

namespace CELL
{
    class   CELLApp
    {
    public:

        /// �������ں���
        virtual bool    createWindow(int width,int height,INSTANCE hInst)  =   0;
        ///  ��ں���
        virtual void    main(int argc,char** argv)  =   0;
    };
}
