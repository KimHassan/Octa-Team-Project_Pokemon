#include "stdafx.h"
#include "mainMenu.h"

mainMenu::mainMenu()
{
}


mainMenu::~mainMenu()
{
}

HRESULT mainMenu::init()  
{
	//버튼들 추가
	_startButton = new button;
	_startButton->init("시작", 400, 654, PointMake(0, 1), PointMake(0, 0), B_start);

	_quitButton = new button;
	_quitButton->init("종료", 400, 708, PointMake(0, 1), PointMake(0, 0), B_quit);

	//메인 메뉴 화면 BGM 재생
	SOUNDMANAGER->play("00_mainTheme", 1.0f);

	return S_OK;
}

void mainMenu::release()  
{

}

void mainMenu::update()	  
{
	_startButton->update();
	_quitButton->update();
}

void mainMenu::render()	  
{
	IMAGEMANAGER->findImage("메인메뉴")->render(getMemDC());

	_startButton->render();
	_quitButton->render();

	//윈도우 기본 커서 제거했으니 커서 생성
	IMAGEMANAGER->findImage("기본커서")->render(getMemDC(), _ptMouse.x - 1, _ptMouse.y - 2);
}

void mainMenu::B_start()
{
	//시작 눌렀으면 메인 메뉴의 BGM은 끈다.
	SOUNDMANAGER->stop("00_mainTheme");

	//스테이지로 이동
	SCENEMANAGER->changeScene("스테이지");
}

void mainMenu::B_quit()
{
	//끄기
	PostQuitMessage(0);
}