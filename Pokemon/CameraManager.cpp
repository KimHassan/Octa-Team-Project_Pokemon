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

    //속도를 한번만 저장하기 위함
    if (!_forOnce)
    {
        _cameraSpeed = speed;
        _forOnce = true;
    }

    //캐릭터용 카메라
    if (isPlayer)
    {
        //캐릭터용 카메라는 카메라의 y좌표와 캐릭터의 중점을 기준으로 속도가 달라짐
        _cameraSpeed = getDistance(x, y, x, _y) * 0.026;
        if (_cameraSpeed <= 5) _cameraSpeed = getDistance(x, y, x, _y) * 0.02;
        if (_cameraSpeed <= 2.5) _cameraSpeed = getDistance(x, y, x, _y) * 0.01;
        
        //처음에 캐릭터까지 카메라가 자동으로 이동
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
        //캐릭터에 도착했을 때 카메라
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
    else //미사일용 카메라
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
