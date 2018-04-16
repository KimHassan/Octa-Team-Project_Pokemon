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

	DWORD _loadingThreadID;	//Ȥ�� ���� �־��µ� ���⼱ �����ʴ� ������� ID

public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//�� �߰� �Լ�
	gameNode* addScene(string sceneName, gameNode* scene);

	//�ε� �� �߰� �Լ� (������ ����)
	gameNode* addLoadingScene(string loadingSceneName, gameNode* scene);

	//�� ����
	HRESULT changeScene(string sceneName);
	HRESULT changeScene(string sceneName, string loadingSceneName);

	bool isSceneUse(gameNode* scene);

	//friend�� ���� �ϸ� Ŭ������ private���� �׳� ������ ����� ���ش�
	//�����ϸ� ĸ��ȭ �ϴ� �ǹ̰� �������µ�, ������ �Լ�, ������ 
	friend DWORD CALLBACK loadingThread(LPVOID prc);
};

