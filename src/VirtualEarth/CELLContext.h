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
		/// ���ĵ�ǰλ��X
		int         _mouseX;
		/// ���ĵ�ǰλ��Y
		int         _mouseY;
	};
}



