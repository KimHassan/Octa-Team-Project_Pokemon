#pragma once
#include "gameNode.h"

//게이지 바
class progressBar : public gameNode
{
private:
	RECT _rcProgress;
	int _x, _y;
	float _width;

	image* _progressBarTop;
	image* _progressBarBottom;

public:
	progressBar();
	~progressBar();

	HRESULT init(int x, int y, int width, int height);
	HRESULT init(char* frontImage, char* backImage, float x, float y, int width, int height);
	void release();
	void update();
	void render();

	void setGauge(float currentGauge, float maxGauge);

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

	//-- private에 추가되있는 _width가 게이지바 위에 부분의 길이사이즈인데
	//-- 그걸 getWidth의 값이 _width의 값으로 되돌려주면 width가 1이면 getWidth도 1이되니까ㅇㅇ
	float getWidth() { return _width; }
};

