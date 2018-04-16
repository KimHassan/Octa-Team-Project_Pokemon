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
	//��ư�� �߰�
	_startButton = new button;
	_startButton->init("����", 400, 654, PointMake(0, 1), PointMake(0, 0), B_start);

	_quitButton = new button;
	_quitButton->init("����", 400, 708, PointMake(0, 1), PointMake(0, 0), B_quit);

	//���� �޴� ȭ�� BGM ���
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
	IMAGEMANAGER->findImage("���θ޴�")->render(getMemDC());

	_startButton->render();
	_quitButton->render();

	//������ �⺻ Ŀ�� ���������� Ŀ�� ����
	IMAGEMANAGER->findImage("�⺻Ŀ��")->render(getMemDC(), _ptMouse.x - 1, _ptMouse.y - 2);
}

void mainMenu::B_start()
{
	//���� �������� ���� �޴��� BGM�� ����.
	SOUNDMANAGER->stop("00_mainTheme");

	//���������� �̵�
	SCENEMANAGER->changeScene("��������");
}

void mainMenu::B_quit()
{
	//����
	PostQuitMessage(0);
}