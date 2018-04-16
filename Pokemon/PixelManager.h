#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

class GameNode;

class PixelManager : public singletonBase<PixelManager>
{
private:
    typedef struct tagPt
    {
		animation *     anim;           //�����ʿ� ����� �ִϸ��̼�
        image *         img;            //�����ʿ� ����� �̹���
		bool            isNapalm;       //���������� �׳� ��������
        bool            onGround;       //���� �浹 ����
        bool            inUse;          //��������� �ƴ���(���� ���� ���� ����)
        float           x, y;           //��ġ
        float           fireX, fireY;   //������ġ
        float           radius;         //�ı��� ���� ����
        float           angle;          //�������� ���� �浹 �������� ����
        float           startAngle;     //�������� ���� �浹���� �ʾ������� ����
        float           count;          //�������� ��� �ð�
        float           gravity;        //�������� �߷�
        float           probeY;         //���� �浹 Ž������
        float           speed;          //�������� �ӵ�

        tagPt()
        {
            anim = NULL;
            img = NULL;
            isNapalm = false;
            onGround = false;
            inUse = false;
            x, y = 0;
            fireX, fireY = 0;
            radius = 0;
            angle = 0;
            startAngle = 0;
            count = 0;
            gravity = 0;
            probeY = 0;
            speed = 0;
        }
    }Pt;

    vector<Pt>               _vPt;      //�ı��� ���� ����
    vector<Pt>::iterator     _viPt;     //�ı��� ���� ���� �ݺ���

public:
    PixelManager();
    ~PixelManager();

    HRESULT Init();
    void Release();
    void Update();
    void Render(HDC hdc);

    //�Ϲ� ��ź �����ı�
    void NormalBomb(float x, float y, float radius);
    //������ �����ı�
	void NapalmBomb(float x, float y, float radius, float num);
    //������ �̵�
    void Move();
};