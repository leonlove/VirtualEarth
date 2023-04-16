#pragma once
#include "CELLOpenGL.h"

namespace CELL {
	class CELLContext
	{
	public:
		CELLContext();
		virtual ~CELLContext();

	public:
		CELLOpenGL* _device;
		/// 鼠标的当前位置X
		int         _mouseX;
		/// 鼠标的当前位置Y
		int         _mouseY;
	};
}



