#pragma once
namespace CELL {
	class CELLInput {
	public:
		/// <summary>
		/// 鼠标左键按下
		/// </summary>
		virtual void    onLButtonDown(int x, int y) = 0;
		/// <summary>
		/// 鼠标左键提起
		/// </summary>
		virtual void    onLButtonUp(int x, int y) = 0;
		/// <summary>
		/// 鼠标移动事件
		/// </summary>
		virtual void    onMouseMove(int x, int y) = 0;
	};
}
