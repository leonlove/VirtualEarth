#pragma once
#include "CELLFrame.hpp"
#include "CELLCamera.hpp"
namespace CELL
{
    class CELLFrameBigMap :public CELLFrame
    {
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
		
    };

}

