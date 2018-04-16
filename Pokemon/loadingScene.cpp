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
		sprintf_s(image, "ĳ���ͼ���â%d", i);
		_loading->loadImage(image, "image/ĳ���ͼ���â.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
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

	//�ε��� �Ϸ�Ǹ�
	if (_loading->loadingDone())
	{
		SCENEMANAGER->changeScene("�÷��̾�");
	}
}

void loadingScene::render()
{
	_loading->render();
}