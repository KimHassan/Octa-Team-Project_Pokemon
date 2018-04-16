#pragma once
#include "gameNode.h"
#include "button.h"

class mainMenu : public gameNode
{
private:
	button* _startButton;
	button* _quitButton;

public:
	mainMenu();
	~mainMenu();

	HRESULT init();
	void release();
	void update();
	void render();

	static void B_start();
	static void B_quit();
};

