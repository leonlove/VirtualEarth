#pragma once

#include    "CELLContext.hpp"
#include    "CELLInput.hpp"
namespace   CELL
{

    class   CELLFrame :public CELLInput
    {
    public:
        CELLContext&    _context;
    public:
        CELLFrame(CELLContext& context)
            :_context(context)
        {}
        virtual ~CELLFrame()
        {}
        /// <summary>
        /// ��������
        /// </summary>
        virtual void    update(CELLContext& context) = 0;
        /// <summary>
        /// ��ʼ����
        /// </summary>
        virtual void    onFrameStart(CELLContext& context)  =   0;

        /// <summary>
        /// ��������
        /// </summary>
        virtual void    onFrameEnd(CELLContext& context)  =   0;

		virtual void    onKeyDown(int key) = 0;
		/// <summary>
		/// ���̰��º��¼�
		/// </summary>
		virtual void    onKeyUp(int key) = 0;

		virtual void	onMouseWheel(int delta) = 0;
    };
}
