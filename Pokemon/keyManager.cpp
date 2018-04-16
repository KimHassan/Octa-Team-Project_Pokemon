#include "stdafx.h"
#include "keyManager.h"


keyManager::keyManager()
{
}


keyManager::~keyManager()
{

}

HRESULT keyManager::init()
{
	for (int i = 0; i < KEYMAX; i++)
	{
		this->getKeyUp().set(i, false);
		this->getKeyUp().set(i, false);
	}

	return S_OK;
}

void keyManager::release()
{

}


bool keyManager::isOnceKeyDown(int key)
{
	//어떤 키를 눌렀다는 신호가 들어오면 (비동기)
	if (GetAsyncKeyState(key) & 0x8000)
	{
		//만약 그 키가 눌러져있지 않은 상태면
		if (!this->getKeyDown()[key])
		{
			//해당 키를 눌렀다고 신호를 보내라
			this->setKeyDown(key, true);
			return true;
		}
		
	}
	else this->setKeyDown(key, false);

	return false;
}

bool keyManager::isOnceKeyUp(int key)  
{
	//역시 해당 키에 신호가 들어오면
	if (GetAsyncKeyState(key) & 0x8000) this->setKeyUp(key, true);
	else
	{
		if (this->getKeyUp()[key])
		{
			this->setKeyUp(key, false);
			return true;
		}
	}

	return false;
}

bool keyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	

	return false;
}

bool keyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;

	return false;
}
