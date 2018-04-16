#pragma once
#include "ship.h"

class battle :	public ship
{
private:

public:
	battle();
	~battle();

	virtual HRESULT init(const char* imageName, int x, int y);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void keyControl(void);

};

