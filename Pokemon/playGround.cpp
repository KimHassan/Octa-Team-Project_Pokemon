#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{

}

HRESULT playGround::init()
{
	gameNode::init(true);
	
	//���߰�
	SCENEMANAGER->addScene("�÷��̾�", new playScene);
	SCENEMANAGER->addScene("�ε���", new loadingScene);
	SCENEMANAGER->addScene("����", new MapTool);
	SCENEMANAGER->changeScene("����");

	CAMERAMANAGER->Init("backBuffer");

	return S_OK;
}

void playGround::release()
{
	gameNode::release();

	
}

void playGround::update()
{
	gameNode::update();

	SCENEMANAGER->update();

}

void playGround::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================================================================

	SCENEMANAGER->render();

	//==================================================================
	//this->getBackBuffer()->render(getHDC(), 0, 0);
	CAMERAMANAGER->Render(getHDC());
}