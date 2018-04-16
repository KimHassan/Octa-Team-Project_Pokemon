#include "stdafx.h"
#include "database.h"


database::database()
{
}


database::~database()
{

}

HRESULT database::init()
{
	loadDatabase("database.txt");

	return S_OK;
}

void database::release()
{

}


//데이터 불러오는 함수
void database::loadDatabase(string name)
{
	arrElements vTemp;
	vTemp = TXTDATA->txtLoad(name.c_str());

	string str;
	int count = 0;	//항목 갯수

	// 0      1      2    3     4     5      6       7
	// |,캐릭터 이름,현체,최체,공격력,방어력,최대속도, 각도

	for (int i = 0; i < vTemp.size(); i++)
	{
		if (vTemp[i] == "|")
		{
			elements* em = new elements;
			str = vTemp[i + 1];

			_mTotalElement.insert(pair<string, elements*>(vTemp[i + 1], em));

			if (i != 0) count += 7;
			continue;
		}

		iterElement mIter = _mTotalElement.find(str);

		if (i == count + 1) mIter->second->name = vTemp[i].c_str();
		else if (i == count + 2) mIter->second->currentHP = atoi(vTemp[i].c_str());
		else if (i == count + 3) mIter->second->maxHP = atoi(vTemp[i].c_str());
		else if (i == count + 4) mIter->second->atk = atoi(vTemp[i].c_str());
		else if (i == count + 5) mIter->second->defense = atoi(vTemp[i].c_str());
		else if (i == count + 6) mIter->second->maxSpeed = atoi(vTemp[i].c_str());
	}

	vTemp.clear();
}


//설정자
void database::setElementDataCurrentHP(string str, float ch)
{
	iterElement mIter = _mTotalElement.find(str);

	mIter->second->currentHP = ch;
}

void database::setElementDataMaxHP(string str, float mh)
{
	iterElement mIter = _mTotalElement.find(str);

	mIter->second->maxHP = mh;
}

void database::setElementDataAtk(string str, float atk)
{
	iterElement mIter = _mTotalElement.find(str);

	mIter->second->atk = atk;
}

void database::setElementDataDef(string str, float def)
{
	iterElement mIter = _mTotalElement.find(str);

	mIter->second->defense = def;
}

void database::setElementDataMaxSpeed(string str, float maxSpeed)

{
	iterElement mIter = _mTotalElement.find(str);

	mIter->second->maxSpeed = maxSpeed;
}
