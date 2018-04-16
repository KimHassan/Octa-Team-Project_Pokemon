#pragma once
#include "gameNode.h"
#include "tileNode.h"

enum CTRL
{
	CTRL_SAVE,			//세이브
	CTRL_LOAD,			//로드
	CTRL_TERRAINDRAW,	//지형
	CTRL_OBJDRAW,		//오브젝트
	CTRL_ERASER,		//이레이져
	CTRL_END
};

class MapTool : public gameNode
{
private:
	//윈도우 버튼 사용을 위한 핸들
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

