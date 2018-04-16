#include "stdafx.h"
#include "pixelCollisionTest.h"


pixelCollisionTest::pixelCollisionTest()
{
}


pixelCollisionTest::~pixelCollisionTest()
{

}

HRESULT pixelCollisionTest::init()
{
	IMAGEMANAGER->addImage("¾ð´ö", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_ball = IMAGEMANAGER->addImage("ball", "ball.bmp", 60, 60, true, RGB(255, 0, 255));


	//°ø ÁßÁ¡ ÁÂÇ¥ ¼ÂÆÃ
	_x = WINSIZEX / 2 - 150;
	_y = WINSIZEY / 2 + 80;

	//ÁßÁ¡ÁÂÇ¥·Î °ø Å©±â¸¸ÇÑ ·ºÆ® »ý¼º
	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());

	//YÅ½»çÃà Àº 
	_probeY = _y + _ball->getHeight() / 2;

	

	return S_OK;
}

void pixelCollisionTest::release()
{

}

void pixelCollisionTest::update() 
{
	if ( KEYMANAGER->isStayKeyDown(VK_LEFT) ) _x -= 3;
	if ( KEYMANAGER->isStayKeyDown(VK_RIGHT) ) _x += 3;

	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());

	for ( int i = _probeY - 50; i < _probeY + 50; ++i )
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("¾ð´ö")->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ( !(r == 255 && g == 0 && b == 255) )
		{
			_y = i - _ball->getHeight() / 2;
			break;
		}
	}

	_destroy = RectMakeCenter(_ptMouse.x, _ptMouse.y, 50, 50);

	if ( KEYMANAGER->isOnceKeyDown(VK_LBUTTON) )
	{
		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
		HBRUSH oldBrush = (HBRUSH) SelectObject(IMAGEMANAGER->findImage("¾ð´ö")->getMemDC(), brush);

		HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
		HPEN oldPen = (HPEN) SelectObject(IMAGEMANAGER->findImage("¾ð´ö")->getMemDC(), pen);

		Ellipse(IMAGEMANAGER->findImage("¾ð´ö")->getMemDC(), _destroy.left, _destroy.top, _destroy.right, _destroy.bottom);
		SelectObject(IMAGEMANAGER->findImage("¾ð´ö")->getMemDC(), brush);
		DeleteObject(brush);
		SelectObject(IMAGEMANAGER->findImage("¾ð´ö")->getMemDC(), pen);
		DeleteObject(pen);

	}


	//YÅ½»çÃà Àº 
	_probeY = _y + _ball->getHeight() / 2;
}

void pixelCollisionTest::render() 
{
	IMAGEMANAGER->findImage("¾ð´ö")->render(getMemDC());

	_ball->render(getMemDC(), _rc.left, _rc.top);

	
}

