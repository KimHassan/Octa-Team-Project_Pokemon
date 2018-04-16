#pragma once
#include "image.h"

//'backBuffer'�� �̸��� ���� �� ��Ʈ���� �ϳ� static���� �����д�
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

class gameNode
{
private:
	HDC _hdc;			//����� DC
	bool _managerInit;	//�Ŵ������� init�Ҳ���

public:
	int _ctrSelect;	//��Ʈ�� ���� ����

	virtual HRESULT init();
	virtual HRESULT init(bool managerInit);
	virtual void release();
	virtual void update();
	virtual void render(void);

	virtual void setMap(void);

	virtual void save(void);
	virtual void load(void);

	void setCtrlSelect(int num) { _ctrSelect = num; }

	//����ۿ� �����ϱ� ���� ������
	image* getBackBuffer() { return _backBuffer; }

	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

	gameNode();
	virtual ~gameNode();
};

