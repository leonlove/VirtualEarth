#pragma once
#include "CELLFrame.hpp"
#include "CELLTimestamp.hpp"
namespace CELL
{
    class CELLFrameBigMap :public CELLFrame
    {
	public:
		CELLTimestamp _timestamp;
    public:
        CELLFrameBigMap(CELLContext& context);

        virtual ~CELLFrameBigMap();

        /// <summary>
        /// ��������
        /// </summary>
        virtual void    update(CELLContext& context);
        /// <summary>
        /// ��ʼ����
        /// </summary>
        virtual void    onFrameStart(CELLContext& context);

        /// <summary>
        /// ��������
        /// </summary>
        virtual void    onFrameEnd(CELLContext& context);

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

		virtual void	onMouseWheel(int delta);
		/// <summary>
		/// ���̰����¼�
		/// </summary>
		virtual void    onKeyDown(int key);
		/// <summary>
		/// ���̰��º��¼�
		/// </summary>
		virtual void    onKeyUp(int key);
    };

}

