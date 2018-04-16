#include "stdafx.h"
#include "CameraManager.h"


CameraManager::CameraManager()
{
}


CameraManager::~CameraManager()
{
}

HRESULT CameraManager::Init(const char * name)
{
    offSetX2 = 0;
    offSetY2 = 0;

    _x = WINSIZEX / 2 - offSetX2;
    _y = WINSIZEY / 2 - offSetY2;

    _cameraSpeed = 0;

    _state = MOVE;

    imageName = name;

    backgroundSizeX = IMAGEMANAGER->findImage(imageName)->getWidth();
    backgroundSizeY = IMAGEMANAGER->findImage(imageName)->getHeight();

    return S_OK;
}

void CameraManager::Release()
{
}

void CameraManager::Update(float x, float y, float speed, bool isPlayer)
{
    _x = WINSIZEX / 2 - offSetX2;
    _y = WINSIZEY / 2 - offSetY2;

    //�ӵ��� �ѹ��� �����ϱ� ����
    if (!_forOnce)
    {
        _cameraSpeed = speed;
        _forOnce = true;
    }

    //ĳ���Ϳ� ī�޶�
    if (isPlayer)
    {
        //ĳ���Ϳ� ī�޶�� ī�޶��� y��ǥ�� ĳ������ ������ �������� �ӵ��� �޶���
        _cameraSpeed = getDistance(x, y, x, _y) * 0.026;
        if (_cameraSpeed <= 5) _cameraSpeed = getDistance(x, y, x, _y) * 0.02;
        if (_cameraSpeed <= 2.5) _cameraSpeed = getDistance(x, y, x, _y) * 0.01;
        
        //ó���� ĳ���ͱ��� ī�޶� �ڵ����� �̵�
        if (_state == MOVE)
        {
            if (_cameraSpeed <= 0) _state = FOLLOW;

            if (offSetX2 <= 0 && offSetX2 > WINSIZEX - backgroundSizeX)
            {
                if (x < _cameraRC.left)
                {
                    offSetX2 += _cameraSpeed;
                    if (offSetX2 > 0) offSetX2 = 0;
                }
                else if (x > _cameraRC.right)
                {
                    offSetX2 += -_cameraSpeed;
                    if (offSetX2 < WINSIZEX - backgroundSizeX) offSetX2 = WINSIZEX - backgroundSizeX;
                }
            }
            if (offSetY2 <= 0 && offSetY2 > WINSIZEY - backgroundSizeY)
            {
                if (y < _cameraRC.top)
                {
                    offSetY2 += _cameraSpeed;
                    if (offSetY2 > 0) offSetY2 = 0;
                }
                else if (y > _cameraRC.bottom)
                {
                    offSetY2 += -_cameraSpeed;
                    if (offSetY2 < WINSIZEY - backgroundSizeY) offSetY2 = WINSIZEY - backgroundSizeY;
                }
            }
        }
        //ĳ���Ϳ� �������� �� ī�޶�
        else if (_state == FOLLOW)
        {
            if (x >= WINSIZEX / 2 && x <= backgroundSizeX - WINSIZEX / 2)
            {
                offSetX2 = -(x - WINSIZEX / 2);
            }

            if (offSetY2 <= 0 && offSetY2 >= WINSIZEY - backgroundSizeY)
            {
                if (y < _cameraRC.top)
                {
                    offSetY2 += _cameraSpeed;
                    if (offSetY2 > 0) offSetY2 = 0;
                }
                else if (y > _cameraRC.bottom)
                {
                    offSetY2 += -_cameraSpeed;
                    if (offSetY2 < WINSIZEY - backgroundSizeY) offSetY2 = WINSIZEY - backgroundSizeY;
                }
            }
        }
    }
    else //�̻��Ͽ� ī�޶�
    {
        _state = MOVE;
        _forOnce = false;

        if (x >= WINSIZEX / 2 && x <= backgroundSizeX - WINSIZEX / 2)
        {
            if (x - 10 <= _cameraRC.left)
            {
                offSetX2 = -(x - (WINSIZEX / 2 - 10));
            }
            else if (x + 10 >= _cameraRC.right)
            {
                offSetX2 = -(x - (WINSIZEX / 2 + 10));
            }
        }
        if (y >= WINSIZEY / 2 && y <= backgroundSizeY - WINSIZEY / 2)
        {
            if (y - 10 <= _cameraRC.top)
            {
                offSetY2 = -(y - (WINSIZEY / 2 - 10));
            }
            else if (y + 10 >= _cameraRC.bottom)
            {
                offSetY2 = -(y - (WINSIZEY / 2 + 10));
            }
        }
    }

    _cameraRC = RectMakeCenter(_x, _y, 100, 40);
}

void CameraManager::Render(HDC hdc)
{
    IMAGEMANAGER->findImage(imageName)->render(hdc, offSetX2, offSetY2);
}
