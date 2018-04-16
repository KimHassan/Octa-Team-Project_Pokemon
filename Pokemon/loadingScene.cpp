#include "stdafx.h"
#include "loadingScene.h"


loadingScene::loadingScene()
{
}


loadingScene::~loadingScene()
{
}

HRESULT loadingScene::init()
{
	_loading = new loading;
	_loading->init();

	char image[256];

	for (int i = 0; i < 400; i++)
	{
		ZeroMemory(image, sizeof(image));
		sprintf_s(image, "캐릭터선택창%d", i);
		_loading->loadImage(image, "image/캐릭터선택창.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	}

	return S_OK;
}

void loadingScene::release()
{
	SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	_loading->update();

	//로딩이 완료되면
	if (_loading->loadingDone())
	{
		SCENEMANAGER->changeScene("플레이씬");
	}
}

void loadingScene::render()
{
	_loading->render();
}