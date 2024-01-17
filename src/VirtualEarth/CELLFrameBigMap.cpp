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
		_context._camera.perspective(45.0f, (real)_context._width / (real)_context._height, 0.1f, 100.0f);
		_context._camera.update();
		_context._vp = _context._camera._matProj *_context._camera._matView;
		_context._timePerFrame = _timestamp.getElapsedSecond();
		_timestamp.update();

		if (_context._keyState[VK_UP])
			_context._camera.moveFront(_context._timePerFrame);
		else if (_context._keyState[VK_DOWN])
			_context._camera.moveBack(_context._timePerFrame);
		else if (_context._keyState[VK_LEFT])
			_context._camera.moveLeft(_context._timePerFrame);
		else if (_context._keyState[VK_RIGHT])
			_context._camera.moveRight(_context._timePerFrame);
    }

    void CELLFrameBigMap::onFrameStart(CELLContext& context)
    {
        context._device->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        context._device->clearColor(0.2f, 0.3f, 0.3f, 1);

        /// 获取shader
        PROGRAM_P3_UC&  prg =   context._resMgr->_PROGRAM_P3_UC;

		static long nElapsed = 1.0;
		nElapsed++;

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
				tmat4x4<double> model;
				model.translate(cubePositions[i]);
				tmat4x4<double> model2;
				float angle = 20.0f * i;
				model = model * model2.rotate(angle, tvec3<float>(1.0f, 0.3f, 0.5f));
				matrix4r mvp = _context._vp * model;
				context._device->setUniformMatrix4fv(prg._mvp, 1, GL_FALSE, mvp.data());
				context._resMgr->_Model.Draw(prg);
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

	void CELLFrameBigMap::onMouseWheel(int delta)
	{
		double persent = 1.0;
		if (delta > 0)
		{
			persent = 0.9;
		}
		else
		{
			persent = 1.1;
		}
		_context._camera.scaleCameraByPos(real3(0, 0, 0), persent);
	}

	void CELLFrameBigMap::onKeyDown(int key)
	{
		_context._keyState[key] = 1;
	}

	void CELLFrameBigMap::onKeyUp(int key)
	{
		_context._keyState[key] = 0;
	}

}

