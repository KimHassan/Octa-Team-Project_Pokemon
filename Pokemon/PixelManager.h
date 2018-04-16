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
		animation *     anim;           //네이팜에 사용할 애니메이션
        image *         img;            //네이팜에 사용할 이미지
		bool            isNapalm;       //네이팜인지 그냥 폭팜인지
        bool            onGround;       //땅과 충돌 여부
        bool            inUse;          //사용중인지 아닌지(렌더 할지 말지 결정)
        float           x, y;           //위치
        float           fireX, fireY;   //시작위치
        float           radius;         //파괴될 지형 범위
        float           angle;          //네이팜이 땅에 충돌 했을때의 각도
        float           startAngle;     //네이팜이 땅에 충돌하지 않았을때의 각도
        float           count;          //네이팜의 사용 시간
        float           gravity;        //네이팜의 중력
        float           probeY;         //땅과 충돌 탐사지점
        float           speed;          //네이팜의 속도

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

    vector<Pt>               _vPt;      //파괴될 지형 벡터
    vector<Pt>::iterator     _viPt;     //파괴될 지형 벡터 반복자

public:
    PixelManager();
    ~PixelManager();

    HRESULT Init();
    void Release();
    void Update();
    void Render(HDC hdc);

    //일반 폭탄 지형파괴
    void NormalBomb(float x, float y, float radius);
    //네이팜 지형파괴
	void NapalmBomb(float x, float y, float radius, float num);
    //네이팜 이동
    void Move();
};