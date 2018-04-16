#include "stdafx.h"
#include "groundManager.h"


groundManager::groundManager()
{
}


groundManager::~groundManager()
{
}

HRESULT groundManager::init()
{
	return S_OK;
}

void groundManager::EllipseDestroy(image* image, RECT rc)
{
	HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
	HBRUSH oldBrush = (HBRUSH)SelectObject(image->getMemDC(), brush); //¾ð´ö¿¡ ¿øÀ» ±×·ÁÁÜ

	HPEN pen = CreatePen(PS_NULL, 1, RGB(255, 0, 255));
	HPEN oldPen = (HPEN)SelectObject(image->getMemDC(), pen);

	Ellipse(image->getMemDC(), rc.left, rc.top, rc.right, rc.bottom);

	SelectObject(image->getMemDC(), oldBrush);
	DeleteObject(brush);

	SelectObject(image->getMemDC(), oldPen);
	DeleteObject(pen);
}

void groundManager::EllipseDestroyCenter(image * image, int x, int y, int width, int height)
{
	HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
	HBRUSH oldBrush = (HBRUSH)SelectObject(image->getMemDC(), brush); //¾ð´ö¿¡ ¿øÀ» ±×·ÁÁÜ

	HPEN pen = CreatePen(PS_NULL, 1, RGB(255, 0, 255));
	HPEN oldPen = (HPEN)SelectObject(image->getMemDC(), pen);

	EllipseMakeCenter(image->getMemDC(), x, y, width, height);

	SelectObject(image->getMemDC(), oldBrush);
	DeleteObject(brush);

	SelectObject(image->getMemDC(), oldPen);
	DeleteObject(pen);
}

void groundManager::RectDestory(image * image, RECT rc)
{
	HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
	HBRUSH oldBrush = (HBRUSH)SelectObject(image->getMemDC(), brush); //¾ð´ö¿¡ ¿øÀ» ±×·ÁÁÜ

	HPEN pen = CreatePen(PS_NULL, 1, RGB(255, 0, 255));
	HPEN oldPen = (HPEN)SelectObject(image->getMemDC(), pen);

	Rectangle(image->getMemDC(), rc.left, rc.top, rc.right, rc.bottom);

	SelectObject(image->getMemDC(), oldBrush);
	DeleteObject(brush);

	SelectObject(image->getMemDC(), oldPen);
	DeleteObject(pen);
}

void groundManager::RectDestroyCenter(image * image, int x, int y, int width, int height)
{
	HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
	HBRUSH oldBrush = (HBRUSH)SelectObject(image->getMemDC(), brush); //¾ð´ö¿¡ ¿øÀ» ±×·ÁÁÜ

	HPEN pen = CreatePen(PS_NULL, 1, RGB(255, 0, 255));
	HPEN oldPen = (HPEN)SelectObject(image->getMemDC(), pen);

	RectangleMakeCenter(image->getMemDC(), x, y, width, height);

	SelectObject(image->getMemDC(), oldBrush);
	DeleteObject(brush);

	SelectObject(image->getMemDC(), oldPen);
	DeleteObject(pen);
}
