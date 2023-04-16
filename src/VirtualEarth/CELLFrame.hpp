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
		/// ���²���
		/// </summary>
		virtual void updateFrame(CELLContext& context) = 0;

		/// <summary>
		/// ��ʼ����
		/// </summary>
		virtual void onBeginFrame(CELLContext& context) = 0;

		/// <summary>
		/// ��������
		/// </summary>
		virtual void onEndFrame(CELLContext& context) = 0;

	public:
		CELLContext _context;
	};
}
