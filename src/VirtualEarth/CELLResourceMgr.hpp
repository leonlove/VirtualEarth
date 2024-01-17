#pragma once
#include "CELLProgramLibary.hpp"
#include "CELLModel.h"

namespace CELL
{
    class   CELLResourceMgr
    {
    public:
        /// 针对绘制屏幕二维数据
        PROGRAM_P2_UC   _PROGRAM_P2_UC;
		/// 针对绘制屏幕三维数据
		PROGRAM_P3_UC   _PROGRAM_P3_UC;

		Model _Model;
    public:
        CELLResourceMgr():_Model("")
        {

		}
        ~CELLResourceMgr()
        {}
    public:
        void    initialize(CELLOpenGL* device)
        {
            _PROGRAM_P2_UC.initialize(device);
			_PROGRAM_P3_UC.initialize(device);
        }

        void    destroy()
        {
            _PROGRAM_P2_UC.destroy();
			_PROGRAM_P3_UC.destroy();
        }
    };
}
