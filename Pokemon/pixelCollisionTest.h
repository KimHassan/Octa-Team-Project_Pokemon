#pragma once
#include "gameNode.h"

class pixelCollisionTest : public gameNode
{
private:
	image* _mountain;		//언덕 이미지
	image* _ball;			//공 이미지

	RECT _rc;
	float _x, _y;			
	int _probeY;			//Y축탐사 변수


	//디스트로이 렉트
	RECT _destroy;


public:
	HRESULT init();
	void release();
	void update();
	void render();


	pixelCollisionTest();
	~pixelCollisionTest();
};

