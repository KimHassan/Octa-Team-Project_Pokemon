#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{

}

HRESULT gameNode::init()
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if ( _managerInit )
	{
		//SetTimer(_hWnd, 1, 10, NULL);
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		SOUNDMANAGER->init();
		TIMEMANAGER->init();
		EFFECTMANAGER->init();
		GROUNDMANAGER->init();
		SCENEMANAGER->init();
		TXTDATA->init();
		INIDATA->init();
		DATABASE->init();
	}

	return S_OK;
}

void gameNode::release()
{
	if ( _managerInit )
	{
		//KillTimer(_hWnd, 1);
		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->releaseSingleton();
		SOUNDMANAGER->releaseSingleton();
		TIMEMANAGER->releaseSingleton();
		EFFECTMANAGER->releaseSingleton();
		GROUNDMANAGER->releaseSingleton();
		CAMERAMANAGER->releaseSingleton();
		SCENEMANAGER->releaseSingleton();
		TXTDATA->releaseSingleton();
		INIDATA->releaseSingleton();
		DATABASE->releaseSingleton();
	}
	
	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update()	
{
	//InvalidateRect(_hWnd, NULL, false);
	SOUNDMANAGER->update();
}

void gameNode::render(void)
{

}

void gameNode::setMap(void)
{

}

void gameNode::save(void)
{

}

void gameNode::load(void)
{

}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//HWND : 윈도우 핸들
	//iMessage : 메시지 구분 번호
	//wParam : 키보드 입력 및 마우스 클릭 구분
	//lParam : 마우스 좌표 입력

	PAINTSTRUCT ps;
	HDC			hdc;		//Handle Device Context

	switch (iMessage)
	{
		case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		this->render();

		EndPaint(hWnd, &ps);
		break;

		case WM_TIMER:
		this->update();
		break;

		case WM_LBUTTONDOWN:
		_leftButtonDown = true;

		this->setMap();		//맵 셋팅
		break;
			
		case WM_LBUTTONUP:
		_leftButtonDown = false;
		break;

		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>LOWORD(lParam);
			_ptMouse.y = static_cast<float>HIWORD(lParam);

			//마우스를 누르고 움직여도 맵이 셋팅이 되게!
			if (_leftButtonDown) this->setMap();
		break;

		//case WM_COMMAND:
		//	switch (LOWORD(wParam))
		//	{
		//	case CTRL_SAVE:
		//		this->save();		//세이브 함수 실행
		//		break;

		//	case CTRL_LOAD:
		//		this->load();		//로드 함수 실행
		//		InvalidateRect(hWnd, NULL, false);	//맵을 부르고 갱신
		//		break;

		//	default:
		//		this->setCtrlSelect(LOWORD(wParam));
		//		break;
		//	}

		//break;

		//윈도우 창이 종료될때 발생하는 메시지
		case WM_DESTROY:
			PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
