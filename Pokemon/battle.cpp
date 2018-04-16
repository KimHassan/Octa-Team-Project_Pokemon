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

	//��Ʋũ������ ���ȵ��� database �̱����� �̿��� database.txt���� �������� �ҷ��´�.
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
	//�����̱�
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

	//�̵� ���� �ݴ�� ����
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		/*float tempSpeed;

		tempSpeed = (_speed * -2) + _speed;

		_speed = tempSpeed;*/

		_angle += PI;
	}
}
