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
		/// 更新操作
		/// </summary>
		virtual void updateFrame(CELLContext& context);

		/// <summary>
		/// 开始绘制
		/// </summary>
		virtual void onBeginFrame(CELLContext& context);

		/// <summary>
		/// 结束绘制
		/// </summary>
		virtual void onEndFrame(CELLContext& context);

		/// <summary>
		/// 鼠标左键按下
		/// </summary>
		virtual void    onLButtonDown(int x, int y);
		/// <summary>
		/// 鼠标左键提起
		/// </summary>
		virtual void    onLButtonUp(int x, int y);
		/// <summary>
		/// 鼠标移动事件
		/// </summary>
		virtual void    onMouseMove(int x, int y);
	};
}


