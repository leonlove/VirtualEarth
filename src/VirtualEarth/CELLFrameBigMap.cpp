#include    "CELLPlatform.hpp"
#include    "CELLFrameBigMap.h"
#include    "CELLOpenGL.h"
#include    "CELLContext.hpp"
#include    "CELLResourceMgr.hpp"
#include    "CELLProgramLibary.hpp"
#include <time.h>


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

        /// 获取shader
        PROGRAM_P3_UC&  prg =   context._resMgr->_PROGRAM_P3_UC;

		clock_t tStart = GetTickCount();
		Sleep(100);
		clock_t tStop = GetTickCount();
		long nElapsed = tStop - tStart;

		tmat4x4<float> model;
		model.rotate(nElapsed%360,tvec3<float>(1.0f,0.0f,0.0f));
		tmat4x4<float> view;
		view.translate(tvec3<float>(0.0f, 0.0f, -3.0f));
		tmat4x4<float> projection;
		projection = CELL::perspective<real>(45.0f, (real)_context._width/(real)_context._height,0.1f,100.0f);
        prg.begin();
        {
			context._device->setUniform1i(prg._texture1, 0);
			context._device->setUniform1i(prg._texture2, 1);
			context._device->setUniformMatrix4fv(prg._model,1, GL_FALSE,model.data());
			context._device->setUniformMatrix4fv(prg._view, 1, GL_FALSE, view.data());
			context._device->setUniformMatrix4fv(prg._projection, 1, GL_FALSE, projection.data());
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

