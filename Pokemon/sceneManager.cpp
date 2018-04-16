#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

sceneManager::sceneManager()
{
}


sceneManager::~sceneManager()
{
}


DWORD CALLBACK loadingThread(LPVOID prc)
{
	//바꿔줄 씬(준비된 씬)을 초기화 한다
	sceneManager::_readyScene->init();

	//현재 씬을 교체할 씬으로 바꾼다
	sceneManager::_currentScene = sceneManager::_readyScene;

	//로딩에 사용된 씬을 해제해주고 교체완료된 씬도 해제
	sceneManager::_loadingScene->release();
	sceneManager::_loadingScene = NULL;
	sceneManager::_readyScene = NULL;

	return 0;
}

gameNode* sceneManager::_currentScene = NULL;
gameNode* sceneManager::_loadingScene = NULL;
gameNode* sceneManager::_readyScene = NULL;

HRESULT sceneManager::init()
{
	_currentScene = NULL;
	_loadingScene = NULL;
	_readyScene = NULL;

	return S_OK;
}

void sceneManager::release()
{
	mapSceneIter miSceneList = _mSceneList.begin();

	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != NULL)
		{
			if (miSceneList->second == _currentScene) miSceneList->second->release();
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}

	_mSceneList.clear();
}

void sceneManager::update()	
{

	if (_currentScene) _currentScene->update();
}

void sceneManager::render()	
{

	if (_currentScene) _currentScene->render();
}


//씬 추가 함수
gameNode* sceneManager::addScene(string sceneName, gameNode* scene)
{
	//씬이 없다면 널 값 반환
	if (!scene) return NULL;

	//추가하려는 씬에 키값을 붙여서 맵에 담는다
	_mSceneList.insert(make_pair(sceneName, scene));

	//해당 씬 반환
	return scene;
}


//로딩 씬 추가 함수 (나중을 위함)
gameNode* sceneManager::addLoadingScene(string loadingSceneName, gameNode* scene)
{
	//씬이 없다면 널 값 반환
	if (!scene) return NULL;

	//로딩하려는 씬에 키값을 붙여서 맵에 담는다
	_mSceneList.insert(make_pair(loadingSceneName, scene));

	//해당 씬 반환
	return scene;
}


//씬 변경
HRESULT sceneManager::changeScene(string sceneName)
{
	mapSceneIter iter = _mSceneList.find(sceneName);

	//못찾았다면	실패 메시지 처리
	if (iter == _mSceneList.end()) return E_FAIL;

	//바꾸려는 씬이 현재 씬이면 오케이 처리
	if (iter->second == _currentScene) return S_OK;

	//씬 교체가 성공(true)되면 초기화를 한다
	if (SUCCEEDED(iter->second->init()))
	{
		//기존에 있던 씬을 해제하고
		if (_currentScene) _currentScene->release();

		//현재씬을 교체할 씬으로 체인지
		_currentScene = iter->second;

		return S_OK;
	}

	return E_FAIL;
}

HRESULT sceneManager::changeScene(string sceneName, string loadingSceneName)
{
	mapSceneIter iter = _mSceneList.find(sceneName);

	//못찾았다면	실패 메시지 처리
	if (iter == _mSceneList.end()) return E_FAIL;

	//바꾸려는 씬이 현재 씬이면 오케이 처리
	if (iter->second == _currentScene) return S_OK;

	//로딩하려는 씬을 찾는다
	mapSceneIter findLoading = _mLoadingSceneList.find(loadingSceneName);

	//로딩씬이 있다면  로딩화면으로 전환
	if (findLoading != _mLoadingSceneList.end()) return changeScene(loadingSceneName);

	//씬 교체가 성공(true)되면 초기화를 한다
	if (SUCCEEDED(iter->second->init()))
	{
		//기존에 있던 씬을 해제하고
		if (_currentScene) _currentScene->release();

		//로딩씬을 찾아서 대입해주고
		_loadingScene = findLoading->second;

		_readyScene = iter->second;

		CloseHandle(CreateThread(NULL, 0, loadingThread, NULL, 0, &_loadingThreadID));

		return S_OK;
	}

	return E_FAIL;
}

bool sceneManager::isSceneUse(gameNode* scene)
{
	mapSceneIter iter = _mSceneList.begin();

	for (iter; iter != _mSceneList.end(); ++iter)
	{
		if (scene == _currentScene)
		{
			return true;
		}
		else
		{
			return false;
		}

		break;
	}
}