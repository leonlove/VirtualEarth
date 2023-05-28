#pragma once

#include "CELLProgramLibary.hpp"
namespace CELL
{
    class   CELLResourceMgr
    {
    public:
        /// ��Ի�����Ļ��ά����
        PROGRAM_P2_UC   _PROGRAM_P2_UC;

    public:
        CELLResourceMgr()
        {}
        ~CELLResourceMgr()
        {}
    public:
        void    initialize(CELLOpenGL* device)
        {
            _PROGRAM_P2_UC.initialize(device);
        }

        void    destroy()
        {
            _PROGRAM_P2_UC.destroy();
        }
    };
}
