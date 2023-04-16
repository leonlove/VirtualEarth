#pragma once

#include "CELLFrame.hpp"
#include "CELLContext.h"

namespace CELL {
	class CELLFrameBigMap:public CELLFrame
	{
	public:
		CELLFrameBigMap(CELLContext& context);
		virtual ~CELLFrameBigMap();

		/// <summary>
		/// ���²���
		/// </summary>
		virtual void updateFrame(CELLContext& context);

		/// <summary>
		/// ��ʼ����
		/// </summary>
		virtual void onBeginFrame(CELLContext& context);

		/// <summary>
		/// ��������
		/// </summary>
		virtual void onEndFrame(CELLContext& context);

		/// <summary>
		/// ����������
		/// </summary>
		virtual void    onLButtonDown(int x, int y);
		/// <summary>
		/// ����������
		/// </summary>
		virtual void    onLButtonUp(int x, int y);
		/// <summary>
		/// ����ƶ��¼�
		/// </summary>
		virtual void    onMouseMove(int x, int y);
	};
}


