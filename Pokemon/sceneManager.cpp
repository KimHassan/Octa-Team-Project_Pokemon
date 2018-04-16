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
	//�ٲ��� ��(�غ�� ��)�� �ʱ�ȭ �Ѵ�
	sceneManager::_readyScene->init();

	//���� ���� ��ü�� ������ �ٲ۴�
	sceneManager::_currentScene = sceneManager::_readyScene;

	//�ε��� ���� ���� �������ְ� ��ü�Ϸ�� ���� ����
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


//�� �߰� �Լ�
gameNode* sceneManager::addScene(string sceneName, gameNode* scene)
{
	//���� ���ٸ� �� �� ��ȯ
	if (!scene) return NULL;

	//�߰��Ϸ��� ���� Ű���� �ٿ��� �ʿ� ��´�
	_mSceneList.insert(make_pair(sceneName, scene));

	//�ش� �� ��ȯ
	return scene;
}


//�ε� �� �߰� �Լ� (������ ����)
gameNode* sceneManager::addLoadingScene(string loadingSceneName, gameNode* scene)
{
	//���� ���ٸ� �� �� ��ȯ
	if (!scene) return NULL;

	//�ε��Ϸ��� ���� Ű���� �ٿ��� �ʿ� ��´�
	_mSceneList.insert(make_pair(loadingSceneName, scene));

	//�ش� �� ��ȯ
	return scene;
}


//�� ����
HRESULT sceneManager::changeScene(string sceneName)
{
	mapSceneIter iter = _mSceneList.find(sceneName);

	//��ã�Ҵٸ�	���� �޽��� ó��
	if (iter == _mSceneList.end()) return E_FAIL;

	//�ٲٷ��� ���� ���� ���̸� ������ ó��
	if (iter->second == _currentScene) return S_OK;

	//�� ��ü�� ����(true)�Ǹ� �ʱ�ȭ�� �Ѵ�
	if (SUCCEEDED(iter->second->init()))
	{
		//������ �ִ� ���� �����ϰ�
		if (_currentScene) _currentScene->release();

		//������� ��ü�� ������ ü����
		_currentScene = iter->second;

		return S_OK;
	}

	return E_FAIL;
}

HRESULT sceneManager::changeScene(string sceneName, string loadingSceneName)
{
	mapSceneIter iter = _mSceneList.find(sceneName);

	//��ã�Ҵٸ�	���� �޽��� ó��
	if (iter == _mSceneList.end()) return E_FAIL;

	//�ٲٷ��� ���� ���� ���̸� ������ ó��
	if (iter->second == _currentScene) return S_OK;

	//�ε��Ϸ��� ���� ã�´�
	mapSceneIter findLoading = _mLoadingSceneList.find(loadingSceneName);

	//�ε����� �ִٸ�  �ε�ȭ������ ��ȯ
	if (findLoading != _mLoadingSceneList.end()) return changeScene(loadingSceneName);

	//�� ��ü�� ����(true)�Ǹ� �ʱ�ȭ�� �Ѵ�
	if (SUCCEEDED(iter->second->init()))
	{
		//������ �ִ� ���� �����ϰ�
		if (_currentScene) _currentScene->release();

		//�ε����� ã�Ƽ� �������ְ�
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