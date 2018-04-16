#pragma once
#include "singletonBase.h"

class CameraManager : public singletonBase<CameraManager>
{
private:
    enum STATE
    {
        MOVE,       //�̻��� ���󰡴� ��
        FOLLOW      //ĳ���� ���󰡴� ��
    };

    float offSetX2;     //������� x��ǥ
    float offSetY2;     //������� y��ǥ
    RECT _cameraRC;     //ī�޶� �����̰� �Ǵ� ����
    float _x, _y;       //ī�޶��� ����
    bool _forOnce;      
    float _cameraSpeed; //ī�޷� �ӵ�

    STATE _state;

    int backgroundSizeX;    //���� ����� X ũ��
    int backgroundSizeY;    //���� ����� Y ũ��

    const char * imageName;
public:
    CameraManager();
    ~CameraManager();

    HRESULT Init(const char * name);
    void Release();
    //void Update(���� ���� x, ���� ���� y, ī�޶� �ӵ�, ĳ���� ���� �ƴ���);
    void Update(float x, float y, float speed, bool isPlayer = false);
    void Render(HDC hdc);

    //ī�޶��� x(left), y(top)��ǥ(�����ƴ�)
    //ī�޶� ������ �ִ°� �ƴ϶� ����ۿ� �׷��� �׸��� �̵���Ű�� 
    //���̱� ������ ������ ��Ÿ���� ���� ��밡��
    inline float GetX() { return -offSetX2; }
    inline float GetY() { return -offSetY2; }
};

