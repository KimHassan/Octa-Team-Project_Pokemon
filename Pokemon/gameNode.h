#pragma once
#include "image.h"

//'backBuffer'란 이름을 가진 빈 비트맵을 하나 static으로 만들어둔다
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

class gameNode
{
private:
	HDC _hdc;			//백버퍼 DC
	bool _managerInit;	//매니져들을 init할꺼냐

public:
	int _ctrSelect;	//컨트롤 관련 변수

	virtual HRESULT init();
	virtual HRESULT init(bool managerInit);
	virtual void release();
	virtual void update();
	virtual void render(void);

	virtual void setMap(void);

	virtual void save(void);
	virtual void load(void);

	void setCtrlSelect(int num) { _ctrSelect = num; }

	//백버퍼에 접근하기 위한 접근자
	image* getBackBuffer() { return _backBuffer; }

	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

	gameNode();
	virtual ~gameNode();
};

