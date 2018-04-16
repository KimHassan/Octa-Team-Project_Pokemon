#pragma once
#include "singletonBase.h"
#include <string>
#include <map>

class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
public:
	typedef map<string, gameNode*>				mapSceneList;
	typedef map<string, gameNode*>::iterator	mapSceneIter;

private:
	static gameNode* _currentScene;
	static gameNode* _loadingScene;
	static gameNode* _readyScene;

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;

	DWORD _loadingThreadID;	//혹시 몰라 넣었는데 여기선 쓰지않는 쓰레드용 ID

public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//씬 추가 함수
	gameNode* addScene(string sceneName, gameNode* scene);

	//로딩 씬 추가 함수 (나중을 위함)
	gameNode* addLoadingScene(string loadingSceneName, gameNode* scene);

	//씬 변경
	HRESULT changeScene(string sceneName);
	HRESULT changeScene(string sceneName, string loadingSceneName);

	bool isSceneUse(gameNode* scene);

	//friend는 선언 하면 클래스의 private까지 그냥 접근을 허용케 해준다
	//남발하면 캡슐화 하는 의미가 없어지는데, 프렌드 함수, 프렌드 
	friend DWORD CALLBACK loadingThread(LPVOID prc);
};

