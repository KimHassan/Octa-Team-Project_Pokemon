#include "stdafx.h"
#include "PixelManager.h"
#include "GameNode.h"   //���۹� ������


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
        //������ �����ı��̰�
        if ((*_viPt).isNapalm)
        {
            //���� �浹���� �ʾҰų� ������϶�
            if(!(*_viPt).onGround || (*_viPt).inUse)
                (*_viPt).img->aniRender(_backBuffer->getMemDC(), (*_viPt).x - (*_viPt).img->getFrameWidth() / 2, (*_viPt).y - (*_viPt).img->getFrameHeight() / 2, (*_viPt).anim);
			EllipseMakeCenter(hdc, (*_viPt).x, (*_viPt).y, (*_viPt).radius * 2, (*_viPt).radius * 2);
        }
        //�Ϲ�����
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
    //�Ϲ������� �����ı� ���� ����
    EFFECTMANAGER->play("NormalBomb", x, y);
    for (int i = 0; i < 3; i++)
    {
        Pt first;
        first.x = x + RND->getFromIntTo(-10, 10);
        first.y = y + RND->getFromIntTo(-10, 10);
        first.radius = 20 + RND->getFromIntTo(-5, 5);

        _vPt.push_back(first);
    }

    //�״��� ������ �����ı� ����
    float _angle = (2 * PI) / num;  //�ѷ��� ������ŭ n���

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
        pt.speed = RND->getFromFloatTo(0.15,0.2);   //�ӵ��� �������� �ؼ� �ڿ�������
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

            //������ �ı��ǰ� �������� �������� �̵���Ű�� ���� 0.1�� �ں��� ����
            if ((*_viPt).count > 0.1)
            {
                for (int i = (*_viPt).probeY - 10; i < (*_viPt).probeY + 10; i++)
                {
                    COLORREF color = GetPixel(IMAGEMANAGER->findImage("Background")->getMemDC(), (*_viPt).x, i);

                    int r = GetRValue(color);
                    int g = GetGValue(color);
                    int b = GetBValue(color);

                    //���� �浿������
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

                    //���� �浹���� �ʾ��� ��
                    if (!(*_viPt).onGround)
                    {
                        float x = (*_viPt).x;
                        float y = (*_viPt).y;

                        //������� ������ �߷����� ���� ���� �Ʒ��� ������
                        (*_viPt).x += cosf((*_viPt).startAngle) * (*_viPt).speed;
                        (*_viPt).y += -sinf((*_viPt).startAngle) * (*_viPt).speed + (*_viPt).gravity;

                        (*_viPt).gravity += 0.0005;

                        //���ư��� ���� ���
                        (*_viPt).angle = getAngle(x, y, (*_viPt).x, (*_viPt).y);
                    }
                }
            } 
            //3�ʰ� ������ ������
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
