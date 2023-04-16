#include "CELLFrameBigMap.h"


namespace CELL {
	CELLFrameBigMap::CELLFrameBigMap(CELLContext& context)
		:CELLFrame(context)
	{
	}


	CELLFrameBigMap::~CELLFrameBigMap()
	{
	}

	void CELLFrameBigMap::updateFrame(CELLContext& context)
	{

	}

	void CELLFrameBigMap::onBeginFrame(CELLContext& context)
	{
		context._device->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		context._device->clearColor(1, 0, 0, 1);
	}

	void CELLFrameBigMap::onEndFrame(CELLContext& context)
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

