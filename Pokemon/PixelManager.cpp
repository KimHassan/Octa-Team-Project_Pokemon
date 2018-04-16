#include "stdafx.h"
#include "PixelManager.h"
#include "GameNode.h"   //백퍼버 쓰려고


PixelManager::PixelManager()
{
}


PixelManager::~PixelManager()
{
}

HRESULT PixelManager::Init()
{
	//EFFECTMANAGER->addEffect("NormalBomb", "NormalBomb.bmp", 1207, 100, 71, 100, 1, 0.5, 30);
	//IMAGEMANAGER->addFrameImage("NapalmBomb", L"NaplamBomb.bmp", 90, 14, 5, 1, true, RGB(255, 0, 255));
    
    return S_OK;
}

void PixelManager::Release()
{
    _vPt.clear();
}

void PixelManager::Update()
{
	EFFECTMANAGER->update();
    Move();
}

void PixelManager::Render(HDC hdc)
{
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
    HBRUSH hOBrush = (HBRUSH)SelectObject(hdc, hBrush);
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
    HPEN hOPen = (HPEN)SelectObject(hdc, hPen);
    for (_viPt = _vPt.begin(); _viPt != _vPt.end(); _viPt++)
    {
        //네이팜 지형파괴이고
        if ((*_viPt).isNapalm)
        {
            //땅과 충돌하지 않았거나 사용중일때
            if(!(*_viPt).onGround || (*_viPt).inUse)
                (*_viPt).img->aniRender(_backBuffer->getMemDC(), (*_viPt).x - (*_viPt).img->getFrameWidth() / 2, (*_viPt).y - (*_viPt).img->getFrameHeight() / 2, (*_viPt).anim);
			EllipseMakeCenter(hdc, (*_viPt).x, (*_viPt).y, (*_viPt).radius * 2, (*_viPt).radius * 2);
        }
        //일반폭팜
        else
			EllipseMakeCenter(hdc, (*_viPt).x, (*_viPt).y, (*_viPt).radius * 2, (*_viPt).radius * 2);
    }
    SelectObject(hdc, hOBrush);
    DeleteObject(hBrush);
    SelectObject(hdc, hOPen);
    DeleteObject(hPen);

	EFFECTMANAGER->render();
}


void PixelManager::NormalBomb(float x, float y, float radius)
{
	EFFECTMANAGER->play("NormalBomb", x, y);
	for (int i = 0; i < 3; i++)
	{
		Pt pt;
		pt.x = x + RND->getFromIntTo(-10, 10);
		pt.y = y + RND->getFromIntTo(-10, 10);
		pt.radius = radius + RND->getFromIntTo(-5, 5);

		_vPt.push_back(pt);
	}
}

void PixelManager::NapalmBomb(float x, float y, float radius, float num)
{
    //일반폭팜의 지형파괴 먼저 생성
    EFFECTMANAGER->play("NormalBomb", x, y);
    for (int i = 0; i < 3; i++)
    {
        Pt first;
        first.x = x + RND->getFromIntTo(-10, 10);
        first.y = y + RND->getFromIntTo(-10, 10);
        first.radius = 20 + RND->getFromIntTo(-5, 5);

        _vPt.push_back(first);
    }

    //그다음 네이팜 지형파괴 생성
    float _angle = (2 * PI) / num;  //뿌려줄 갯수만큼 n등분

    for (int i = 0; i < num; i++)
    {
        Pt pt;
        pt.x = x;
        pt.y = y;
        pt.fireX = x;
        pt.fireY = y;
        pt.radius = radius;
        pt.isNapalm = true;
        pt.inUse = false;
        pt.startAngle = _angle * i;
        pt.count = 0;
        pt.gravity = 0;
        pt.speed = RND->getFromFloatTo(0.15,0.2);   //속도를 랜덤으로 해서 자연스럽게
        pt.probeY = pt.y;
        pt.img = IMAGEMANAGER->findImage("NapalmBomb");
        pt.anim = new animation;
        pt.anim->init(pt.img->getWidth(), pt.img->getHeight(), pt.img->getFrameWidth(), pt.img->getFrameHeight());
        pt.anim->setDefPlayFrame(false, true);
        pt.anim->setFPS(1.0f);
        pt.anim->start();

        _vPt.push_back(pt);
    }
}

void PixelManager::Move()
{
    for (_viPt = _vPt.begin(); _viPt != _vPt.end(); )
    {
        if ((*_viPt).isNapalm)
        {
            (*_viPt).count += TIMEMANAGER->getElapsedTime();
            
            (*_viPt).probeY = (*_viPt).y;

            (*_viPt).anim->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);

            //지형이 파괴되고 나서부터 네이팜을 이동시키기 위해 0.1초 뒤부터 실행
            if ((*_viPt).count > 0.1)
            {
                for (int i = (*_viPt).probeY - 10; i < (*_viPt).probeY + 10; i++)
                {
                    COLORREF color = GetPixel(IMAGEMANAGER->findImage("Background")->getMemDC(), (*_viPt).x, i);

                    int r = GetRValue(color);
                    int g = GetGValue(color);
                    int b = GetBValue(color);

                    //땅과 충동했을때
                    if (!(r == 255 && g == 0 && b == 255))
                    {
                        (*_viPt).x += cosf((*_viPt).angle + RND->getFromFloatTo(-PI / 2, PI / 2)) * 0.3;
                        (*_viPt).y += -sinf((*_viPt).angle + RND->getFromFloatTo(-PI / 2, PI / 2)) * 0.3;

                        (*_viPt).onGround = true;
                        (*_viPt).inUse = true;
                        break;
                    }
                    else
                        (*_viPt).inUse = false;

                    //땅과 충돌하지 않았을 때
                    if (!(*_viPt).onGround)
                    {
                        float x = (*_viPt).x;
                        float y = (*_viPt).y;

                        //사방으로 퍼지고 중력으로 인해 점점 아래로 떨어짐
                        (*_viPt).x += cosf((*_viPt).startAngle) * (*_viPt).speed;
                        (*_viPt).y += -sinf((*_viPt).startAngle) * (*_viPt).speed + (*_viPt).gravity;

                        (*_viPt).gravity += 0.0005;

                        //날아가던 각도 계산
                        (*_viPt).angle = getAngle(x, y, (*_viPt).x, (*_viPt).y);
                    }
                }
            } 
            //3초가 지나면 지워줌
            if ((*_viPt).count > 3.0)
            {
                _viPt = _vPt.erase(_viPt);
                (*_viPt).isNapalm = false;
            }
            else _viPt++;
        }
        else _viPt++;
    }
}
