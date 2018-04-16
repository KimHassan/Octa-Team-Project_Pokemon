#pragma once
#include "gameNode.h"

class pixelCollisionTest : public gameNode
{
private:
	image* _mountain;		//��� �̹���
	image* _ball;			//�� �̹���

	RECT _rc;
	float _x, _y;			
	int _probeY;			//Y��Ž�� ����


	//��Ʈ���� ��Ʈ
	RECT _destroy;


public:
	HRESULT init();
	void release();
	void update();
	void render();


	pixelCollisionTest();
	~pixelCollisionTest();
};

