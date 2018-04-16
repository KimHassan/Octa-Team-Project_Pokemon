#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

//�Ӽ�
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

	//������ �ҷ����� �Լ�
	void loadDatabase(string name);

	//�Ӽ��� ���� ������
	elements* getElementData(string str) { return _mTotalElement.find(str)->second; }

	//������
	void setElementDataCurrentHP(string str, float ch);
	void setElementDataMaxHP(string str, float mh);
	void setElementDataAtk(string str, float atk);
	void setElementDataDef(string str, float def);
	void setElementDataMaxSpeed(string str, float maxSpeed);

	void setAngle(float angle) { _angle = angle; }
	float getAngle() { return _angle; }

};

