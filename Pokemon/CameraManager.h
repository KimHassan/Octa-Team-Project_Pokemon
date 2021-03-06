#pragma once
#include "singletonBase.h"

class CameraManager : public singletonBase<CameraManager>
{
private:
    enum STATE
    {
        MOVE,       //미사일 따라가는 용
        FOLLOW      //캐릭터 따라가는 용
    };

    float offSetX2;     //백버퍼의 x좌표
    float offSetY2;     //백버퍼의 y좌표
    RECT _cameraRC;     //카메라가 움직이게 되는 영역
    float _x, _y;       //카메라의 중점
    bool _forOnce;      
    float _cameraSpeed; //카메로 속도

    STATE _state;

    int backgroundSizeX;    //실제 배경의 X 크기
    int backgroundSizeY;    //실제 배경의 Y 크기

    const char * imageName;
public:
    CameraManager();
    ~CameraManager();

    HRESULT Init(const char * name);
    void Release();
    //void Update(따라갈 놈의 x, 따라갈 놈의 y, 카메라 속도, 캐릭터 인지 아닌지);
    void Update(float x, float y, float speed, bool isPlayer = false);
    void Render(HDC hdc);

    //카메라의 x(left), y(top)좌표(중점아님)
    //카메라가 실제로 있는게 아니라 백버퍼에 그려진 그림을 이동시키는 
    //것이기 때문에 음수로 나타내야 쉽게 사용가능
    inline float GetX() { return -offSetX2; }
    inline float GetY() { return -offSetY2; }
};

