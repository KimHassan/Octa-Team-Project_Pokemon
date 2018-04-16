#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{
}


progressBar::~progressBar()
{

}

HRESULT progressBar::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);
	_progressBarTop = IMAGEMANAGER->addImage("frontBar", "hpBarTop.bmp", x, y, width, height, true, RGB(255, 0, 255));
	_progressBarBottom = IMAGEMANAGER->addImage("backBar",
		"hpBarBottom.bmp", x, y, width, height, true, RGB(255, 0, 255));

	//게이지바의 이미지의 길이
	_width = _progressBarTop->getWidth();

	return S_OK;
}

HRESULT progressBar::init(char* frontImage, char* backImage, float x, float y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);

	char strTopImageName[128];
	char strBottomImageName[128];

	ZeroMemory(strTopImageName, sizeof(strTopImageName));
	ZeroMemory(strBottomImageName, sizeof(strBottomImageName));

	//이미지 이름 뒤에 bmp를 붙여준다
	sprintf(strTopImageName, "%s.bmp", frontImage);
	sprintf(strBottomImageName, "%s.bmp", backImage);

	_progressBarBottom = IMAGEMANAGER->addImage(backImage, strBottomImageName, x, y, width, height, true, RGB(255, 0, 255));
	_progressBarTop = IMAGEMANAGER->addImage(frontImage, strTopImageName, x, y, width, height, true, RGB(255, 0, 255));

	_width = _progressBarTop->getWidth();

	return S_OK;
}

void progressBar::release()
{

}

void progressBar::update()
{
	_rcProgress = RectMakeCenter(_x, _y, _progressBarTop->getWidth(), _progressBarTop->getHeight());
}

void progressBar::render()
{
	/*
	//프로그레스 바 (뒤)
	IMAGEMANAGER->render("backBar",
	getMemDC(),
	_rcProgress.left + _progressBarBottom->getWidth() / 2,
	_y + _progressBarBottom->getHeight() / 2,
	0, 0,
	_progressBarBottom->getWidth(), _progressBarBottom->getHeight());

	//프로그레스 바 (앞)
	IMAGEMANAGER->render("frontBar", getMemDC(),
	_rcProgress.left + _progressBarBottom->getWidth() / 2,
	_y + _progressBarBottom->getHeight() / 2,
	0, 0,
	_width, _progressBarBottom->getHeight());
	*/

	_progressBarBottom->render(getMemDC(), _rcProgress.left, _y, 0, 0, _progressBarBottom->getWidth(), _progressBarBottom->getHeight());
	_progressBarTop->render(getMemDC(), _rcProgress.left, _y, 0, 0, _width, _progressBarTop->getHeight());
}

//게이지 백분율
void progressBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBarBottom->getWidth();
}

