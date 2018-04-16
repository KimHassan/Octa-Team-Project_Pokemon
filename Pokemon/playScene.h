#pragma once
#include "gameNode.h"

class playScene : public gameNode
{
public:
	HRESULT init();
	void release();
	void update();
	void render();

	playScene();
	~playScene();
};

