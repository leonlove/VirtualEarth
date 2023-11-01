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
		context._camera.setEye(real3(0.0f, 0.0f, 3.0f));
		context._camera.setTarget(real3(0.0f, 0.0f, 0.0f));
		context._camera.calcDir();

		context._camera.setUp(real3(0.0f, 1.0f, 0.0f));
		context._camera.setRight(real3(1.0f, 0.0f, 0.0f));
    }

    CELLFrameBigMap::~CELLFrameBigMap()
    {
    }

    void CELLFrameBigMap::update(CELLContext& context)
    {
        _context._device->setViewPort(0,0,_context._width,_context._height);
		_context._camera.update();
    }

    void CELLFrameBigMap::onFrameStart(CELLContext& context)
    {
        context._device->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        context._device->clearColor(0.2f, 0.3f, 0.3f, 1);

        /// 获取shader
        PROGRAM_P3_UC&  prg =   context._resMgr->_PROGRAM_P3_UC;

		static long nElapsed = 1.0;
		nElapsed++;
		
		tmat4x4<float> projection;
		projection = CELL::perspective<real>(45.0f, (real)_context._width/(real)_context._height,0.1f,100.0f);

		tvec3<float> cubePositions[] = {
			tvec3<float>(0.0f,  0.0f,  0.0f),
			tvec3<float>(2.0f,  5.0f, -15.0f),
			tvec3<float>(-1.5f, -2.2f, -2.5f),
			tvec3<float>(-3.8f, -2.0f, -12.3f),
			tvec3<float>(2.4f, -0.4f, -3.5f),
			tvec3<float>(-1.7f,  3.0f, -7.5f),
			tvec3<float>(1.3f, -2.0f, -2.5f),
			tvec3<float>(1.5f,  2.0f, -2.5f),
			tvec3<float>(1.5f,  0.2f, -1.5f),
			tvec3<float>(-1.3f,  1.0f, -1.5f)
		};

        prg.begin();
        {
			for (int i = 0; i < 10; i++)
			{
				tmat4x4<float> model;
				model.translate(cubePositions[i]);
				tmat4x4<float> model2;
				float angle = 20.0f * i;
				model = model * model2.rotate(angle, tvec3<float>(1.0f, 0.3f, 0.5f));
				context._device->setUniformMatrix4fv(prg._model, 1, GL_FALSE, model.data());
				context._device->setUniformMatrix4fv(prg._view, 1, GL_FALSE, _context._camera.getView().data());
				context._device->setUniformMatrix4fv(prg._projection, 1, GL_FALSE, projection.data());
				context._resMgr->_Model.Draw();
			}
			context._device->setUniform1i(prg._texture1, 0);
			context._device->setUniform1i(prg._texture2, 1);
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

