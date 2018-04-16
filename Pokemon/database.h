#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

//속성
class elements
{
public:
	const char* name;
	int currentHP;
	int maxHP;
	int atk;
	int defense;
	int maxSpeed;

	elements(){};
	~elements(){};
};

class database : public singletonBase<database>
{
private:
	typedef vector<string>				arrElements;
	typedef vector<string>::iterator	iterElements;

	typedef map<string, elements*>				arrElement;
	typedef map<string, elements*>::iterator	iterElement;

private:
	arrElement _mTotalElement;
	float		_angle;

public:
	database();
	~database();

	HRESULT init();
	void release();

	//데이터 불러오는 함수
	void loadDatabase(string name);

	//속성에 대한 접근자
	elements* getElementData(string str) { return _mTotalElement.find(str)->second; }

	//설정자
	void setElementDataCurrentHP(string str, float ch);
	void setElementDataMaxHP(string str, float mh);
	void setElementDataAtk(string str, float atk);
	void setElementDataDef(string str, float def);
	void setElementDataMaxSpeed(string str, float maxSpeed);

	void setAngle(float angle) { _angle = angle; }
	float getAngle() { return _angle; }

};

