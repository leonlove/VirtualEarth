#pragma once
#include "CELLContext.h"
#include "CELLInput.hpp"

namespace CELL {

	class CELLFrame :public CELLInput {
	public:
		CELLFrame(CELLContext& context)
			:_context(context)
		{

		}

		virtual ~CELLFrame() {

		}

	public:
		/// <summary>
		/// 更新操作
		/// </summary>
		virtual void updateFrame(CELLContext& context) = 0;

		/// <summary>
		/// 开始绘制
		/// </summary>
		virtual void onBeginFrame(CELLContext& context) = 0;

		/// <summary>
		/// 结束绘制
		/// </summary>
		virtual void onEndFrame(CELLContext& context) = 0;

	public:
		CELLContext _context;
	};
}
