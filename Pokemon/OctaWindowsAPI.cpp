#include "stdafx.h"
#include "playGround.h"

//API : Application Programming Interface ���Ӹ�

//============= ���� ���� ���� ��ġ ===================
HINSTANCE _hInstance;		//�ν��Ͻ� ��ȣ
HWND	  _hWnd;			//�ڵ�
			
POINT _ptMouse;		//���콺 ��ǥ
playGround _pg;

BOOL _leftButtonDown;

//====================================================

//================= �Լ� ������Ÿ�� ���� =================
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//========================================================

//Ŭ���̾�Ʈ ���� �������� ���� �Լ� ����(����)
void setWindowSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG			message;	//�޼��� ����ü
	WNDCLASS	wndClass;	//������ ������ ��� ����ü

	//�ν��Ͻ� ��ȣ ����
	_hInstance = hInstance;

	//������ ������ ���� �����Ѵ�
	wndClass.cbClsExtra = 0;										//Ŭ���� ���� �޸� ����
	wndClass.cbWndExtra = 0;										//������ ���� �޸� ����
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//������ ���� ����
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//������ Ŀ�� ��� ����
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//���� ������ ��� ����
	wndClass.hInstance = hInstance;									//������ �ν��Ͻ� ��ȣ
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//������ ���ν���
	wndClass.lpszClassName = WINNAME;								//������ Ŭ���� �̸�
	wndClass.lpszMenuName = NULL;									//������ �޴� �̸�
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//������ â ��Ÿ��

	//������ ���� ������ �����ٸ� ��� ������
	RegisterClass(&wndClass);

	//���� ������ ������ ������ ���� ������ â ���¸� ����
	_hWnd = CreateWindow(
		WINNAME,
		WINNAME,
		WS_OVERLAPPEDWINDOW,	//������ ��Ÿ��
		WINSTARTX,				//������ â ������ǥ X
		WINSTARTY,				//������ â ������ǥ Y
		WINSIZEX,				//������ ����ũ��
		WINSIZEY,				//������ ����ũ��
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);
		
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	//������ ������ â�� ����Ϳ� ����ִ� �Լ�
	ShowWindow(_hWnd, cmdShow);

	//������ �޽��� ���� ������
	if (FAILED(_pg.init()))
	{

		return 0;
	}

	//�������ۿ� Ÿ�̸�
	while ( true )
	{
		if ( PeekMessage(&message, NULL, 0, 0, PM_REMOVE) )
		{
			if ( message.message == WM_QUIT ) break;
			TranslateMessage(&message);	//Ű���� �Է� Ȥ�� ���콺 Ŭ�� �޽����� ó�� ���
			DispatchMessage(&message);	//������ �����쿡 �޽����� �������ִ� ���� ���
		}
		else
		{
			TIMEMANAGER->update(60.0f);
			_pg.update();
			_pg.render();
		}
	}

	//while (GetMessage(&message, 0, 0, 0))
	//{
	//	TranslateMessage(&message);			//Ű���� �Է� Ȥ�� ���콺 Ŭ�� �޽����� ó�� ���
	//	DispatchMessage(&message);			//������ �����쿡 �޽����� �������ִ� ���� ���
	//}

	_pg.release();

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _pg.MainProc(hWnd, iMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height)
{
	//������ ��Ʈ
	RECT winRect;

	winRect.left	= 0;
	winRect.top		= 0;
	winRect.right	= width;
	winRect.bottom	= height;

	//������ ���� ���� �Լ� (����� ��Ʈ, ������ ��Ÿ��, �޴� �� ��뿩��)
	AdjustWindowRect(&winRect, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);
}