#pragma once
#include <vector>
#include "gameNode.h"
#include "MapTool.h"
#include "loadingScene.h"
#include "playScene.h"

struct tagZ
{
	float x, y;
	int order;
	RECT rc;
	RECT shadowRC;
	image* img;
	//RENDER_TYPE type;
	BOOL player;
	BOOL direction;
};

class playGround : public gameNode
{
private:
	vector<tagZ>			_vZ;
	vector<tagZ>::iterator	_viZ;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(void);

	playGround();
	~playGround();
};

