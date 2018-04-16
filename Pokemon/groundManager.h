#pragma once
#include "singletonBase.h"

class groundManager :
	public singletonBase<groundManager>
{
public:
	groundManager();
	~groundManager();

	HRESULT init();
	
	void EllipseDestroy(image* image, RECT rc);
	void EllipseDestroyCenter(image* image, int x, int y, int width, int height);
	void RectDestory(image* image, RECT rc);
	void RectDestroyCenter(image* image, int x, int y, int width, int height);
};

