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
	//HWND : ������ �ڵ�
	//iMessage : �޽��� ���� ��ȣ
	//wParam : Ű���� �Է� �� ���콺 Ŭ�� ����
	//lParam : ���콺 ��ǥ �Է�

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

		this->setMap();		//�� ����
		break;
			
		case WM_LBUTTONUP:
		_leftButtonDown = false;
		break;

		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>LOWORD(lParam);
			_ptMouse.y = static_cast<float>HIWORD(lParam);

			//���콺�� ������ �������� ���� ������ �ǰ�!
			if (_leftButtonDown) this->setMap();
		break;

		//case WM_COMMAND:
		//	switch (LOWORD(wParam))
		//	{
		//	case CTRL_SAVE:
		//		this->save();		//���̺� �Լ� ����
		//		break;

		//	case CTRL_LOAD:
		//		this->load();		//�ε� �Լ� ����
		//		InvalidateRect(hWnd, NULL, false);	//���� �θ��� ����
		//		break;

		//	default:
		//		this->setCtrlSelect(LOWORD(wParam));
		//		break;
		//	}

		//break;

		//������ â�� ����ɶ� �߻��ϴ� �޽���
		case WM_DESTROY:
			PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
