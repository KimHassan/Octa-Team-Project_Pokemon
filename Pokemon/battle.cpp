#include "stdafx.h"
#include "battle.h"


battle::battle()
{
}


battle::~battle()
{

}

HRESULT battle::init(const char* imageName, int x, int y)
{
	ship::init(imageName, x, y);

	//배틀크루저의 스탯들을 database 싱글톤을 이용해 database.txt에서 정보들을 불러온다.
	this->setMaxHp(DATABASE->getElementData("battle")->maxHP);
	this->setCurrentHp(DATABASE->getElementData("battle")->currentHP);
	this->setAtk(DATABASE->getElementData("battle")->atk);
	this->setDef(DATABASE->getElementData("battle")->defense);
	this->setMaxSpeed(DATABASE->getElementData("battle")->maxSpeed);

	return S_OK;
}

void battle::release(void)
{

}

void battle::update(void) 
{
	ship::update();
}

void battle::render(void) 
{
	ship::render();
}


void battle::keyControl(void)
{
	//움직이기
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (_speed < _maxSpeed)
		{
			_speed += 0.04f;
		}
		else
		{
			_speed = 3.0f;
		}
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (_speed > -_maxSpeed)
		{
			_speed -= 0.04f;
		}
		else
		{
			_speed = -3.0f;
		}
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_angle -= 0.04f;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_angle += 0.04f;
	}

	//이동 방향 반대로 교정
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		/*float tempSpeed;

		tempSpeed = (_speed * -2) + _speed;

		_speed = tempSpeed;*/

		_angle += PI;
	}
}
