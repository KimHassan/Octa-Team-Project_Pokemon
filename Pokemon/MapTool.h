#pragma once
#include "gameNode.h"
#include "tileNode.h"

enum CTRL
{
	CTRL_SAVE,			//���̺�
	CTRL_LOAD,			//�ε�
	CTRL_TERRAINDRAW,	//����
	CTRL_OBJDRAW,		//������Ʈ
	CTRL_ERASER,		//�̷�����
	CTRL_END
};

class MapTool : public gameNode
{
private:
	//������ ��ư ����� ���� �ڵ�
	HWND _btnSave;
	HWND _btnLoad;
	HWND _btnTerrainDraw;
	HWND _btnObjectDraw;
	HWND _btnEraser;

	tagCurrentTile	_currentTile;
	tagSampleTile	_sampleTile[SAMPLETILEX * SAMPLETILEY];
	tagTile			_tiles[TILEX * TILEY];

	int _pos[2];

public:
	HRESULT init();
	void release();
	void update();
	void render(void);

	void setup();
	void setMap();

	void save();
	void load();

	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objSelect(int frameX, int frameY);

	MapTool();
	~MapTool();
};

