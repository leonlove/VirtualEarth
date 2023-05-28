#pragma once

namespace CELL
{
    class   CELLInput
    {
    public:
        /// <summary>
        /// ??????
        /// </summary>
        virtual void    onLButtonDown(int x,int y)  =   0;
        /// <summary>
        /// ??????
        /// </summary>
        virtual void    onLButtonUp(int x, int y) = 0;
        /// <summary>
        /// ??????
        /// </summary>
        virtual void    onMouseMove(int x,int y)    =   0;

    };
}
