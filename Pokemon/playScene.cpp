#include "stdafx.h"
#include "playScene.h"


playScene::playScene()
{
}


playScene::~playScene()
{

}

HRESULT playScene::init()
{

	return S_OK;
}

void playScene::release()
{

}

void playScene::update() 
{

}

void playScene::render() 
{
	IMAGEMANAGER->findImage("캐릭터선택창0")->render(getMemDC(), 0, 0);
}
