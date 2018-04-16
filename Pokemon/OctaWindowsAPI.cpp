#include "stdafx.h"
#include "playGround.h"

//API : Application Programming Interface 줄임말

//============= 전역 변수 설정 위치 ===================
HINSTANCE _hInstance;		//인스턴스 번호
HWND	  _hWnd;			//핸들
			
POINT _ptMouse;		//마우스 좌표
playGround _pg;

BOOL _leftButtonDown;

//====================================================

//================= 함수 프로토타입 선언 =================
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//========================================================

//클라이언트 영역 재조정을 위한 함수 선언(전방)
void setWindowSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG			message;	//메세지 구조체
	WNDCLASS	wndClass;	//윈도우 정보를 담는 구조체

	//인스턴스 번호 대입
	_hInstance = hInstance;

	//윈도우 정보를 먼저 셋팅한다
	wndClass.cbClsExtra = 0;										//클래스 여분 메모리 설정
	wndClass.cbWndExtra = 0;										//윈도우 여분 메모리 설정
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//윈도우 배경색 설정
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//윈도우 커서 모양 설정
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//어플 아이콘 모양 설정
	wndClass.hInstance = hInstance;									//윈도우 인스턴스 번호
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//윈도우 프로시져
	wndClass.lpszClassName = WINNAME;								//윈도우 클래스 이름
	wndClass.lpszMenuName = NULL;									//윈도우 메뉴 이름
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//윈도우 창 스타일

	//윈도우 정보 셋팅이 끝났다면 등록 해주자
	RegisterClass(&wndClass);

	//위에 셋팅한 윈도우 정보를 토대로 윈도우 창 형태를 구축
	_hWnd = CreateWindow(
		WINNAME,
		WINNAME,
		WS_OVERLAPPEDWINDOW,	//윈도우 스타일
		WINSTARTX,				//윈도우 창 시작좌표 X
		WINSTARTY,				//윈도우 창 시작좌표 Y
		WINSIZEX,				//윈도우 가로크기
		WINSIZEY,				//윈도우 세로크기
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);
		
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	//실제로 윈도우 창을 모니터에 띄워주는 함수
	ShowWindow(_hWnd, cmdShow);

	//윈도우 메시지 루프 이전에
	if (FAILED(_pg.init()))
	{

		return 0;
	}

	//게임제작용 타이머
	while ( true )
	{
		if ( PeekMessage(&message, NULL, 0, 0, PM_REMOVE) )
		{
			if ( message.message == WM_QUIT ) break;
			TranslateMessage(&message);	//키보드 입력 혹은 마우스 클릭 메시지를 처리 담당
			DispatchMessage(&message);	//실제로 윈도우에 메시지를 전달해주는 역할 담당
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
	//	TranslateMessage(&message);			//키보드 입력 혹은 마우스 클릭 메시지를 처리 담당
	//	DispatchMessage(&message);			//실제로 윈도우에 메시지를 전달해주는 역할 담당
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
	//윈도우 렉트
	RECT winRect;

	winRect.left	= 0;
	winRect.top		= 0;
	winRect.right	= width;
	winRect.bottom	= height;

	//윈도우 영역 조정 함수 (사용할 렉트, 윈도우 스타일, 메뉴 바 사용여부)
	AdjustWindowRect(&winRect, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);
}