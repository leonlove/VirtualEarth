#include    "CELLPlatform.hpp"
#include    "CELLFrameBigMap.h"
#include    "CELLOpenGL.h"
#include    "CELLContext.hpp"
#include    "CELLResourceMgr.hpp"
#include    "CELLProgramLibary.hpp"


namespace CELL
{

    CELLFrameBigMap::CELLFrameBigMap(CELLContext& context)
        :CELLFrame(context)
    {

    }

    CELLFrameBigMap::~CELLFrameBigMap()
    {
    }

    void CELLFrameBigMap::update(CELLContext& )
    {
        _context._device->setViewPort(0,0,_context._width,_context._height);
        //_context._screenPrj =   CELL::ortho<real>(0.0f,(real)_context._width,(real)_context._height,0,-1000.0f,1000.0f);
    }

    void CELLFrameBigMap::onFrameStart(CELLContext& context)
    {
        context._device->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        context._device->clearColor(0.2f, 0.3f, 0.3f, 1);

        /// »ñÈ¡shader
        PROGRAM_P3_UC&  prg =   context._resMgr->_PROGRAM_P3_UC;

		//float timeValue = rand() % 100;
		//float greenValue = (sin(timeValue) / 2.0f);
        prg.begin();
        {
			//context._device->setUniform4f(prg._color, greenValue, greenValue, 0.0f, 1.0f);
			context._resMgr->_Model.Draw();            
        }
        prg.end();

    }

    void CELLFrameBigMap::onFrameEnd(CELLContext& context)
    {
    }

    void CELLFrameBigMap::onLButtonDown(int x, int y)
    {
    }

    void CELLFrameBigMap::onLButtonUp(int x, int y)
    {
    }

    void CELLFrameBigMap::onMouseMove(int x, int y)
    {
    }

}

