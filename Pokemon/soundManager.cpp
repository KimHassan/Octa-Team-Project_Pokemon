#include "stdafx.h"
#include "soundManager.h"


soundManager::soundManager()
	: _system(NULL), _channel(NULL), _sound(NULL)
{
}


soundManager::~soundManager()
{

}

HRESULT soundManager::init()
{
	//FMOD 사운드엔진 초기화
	System_Create(&_system);

	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);

	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	ZeroMemory(_sound, sizeof(_sound));
	ZeroMemory(_channel, sizeof(_channel));

	return S_OK;
}

void soundManager::release()
{
	//사운드 삭제
	if (_channel != NULL || _sound != NULL)
	{
		for (int i = 0; i < TOTALSOUNDBUFFER; i++)
		{
			if (_channel != NULL)
			{
				if (_channel[i]) _channel[i]->stop();
			}

			if (_sound != NULL)
			{
				if (_sound != NULL) _sound[i]->release();
			}
		}
	}

	//메모리 지우기
	SAFE_DELETE_ARRAY(_channel);
	SAFE_DELETE_ARRAY(_sound);

	//시스템 닫기 
	if (_system != NULL)
	{
		_system->release();
		_system->close();
	}
}


//=============================이 거 추 가 ====================================
void soundManager::update()
{
	//사운드 System 계속적으로 업데이트
	_system->update();

	//볼륨이 바뀌거나 
	//재생이 끝난 사운드를 채널에서 빼내는등의 다양한
	//작업을 자동으로 해준다
}


void soundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	if (loop)
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, NULL,
				&_sound[_mTotalSounds.size()]);
		}
	}
	else
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_DEFAULT, NULL, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_DEFAULT, NULL,
				&_sound[_mTotalSounds.size()]);
		}
	}

	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}


//0 ~ 255 -> 0.0 ~ 1.0f
void soundManager::play(string keyName, float volume)
{
	//이터레이터에 맵컨테이너 처음을 가르키게 해주고
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;		//배열 탐색을 위한 카운트

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);

			_channel[count]->setVolume(volume);
			break;
		}
	}
}

void soundManager::stop(string keyName)
{
	//이터레이터에 맵컨테이너 처음을 가르키게 해주고
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;		//배열 탐색을 위한 카운트

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			break;
		}
	}
}

void soundManager::pause(string keyName)
{
	//이터레이터에 맵컨테이너 처음을 가르키게 해주고
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;		//배열 탐색을 위한 카운트

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void soundManager::resume(string keyName)
{
	//이터레이터에 맵컨테이너 처음을 가르키게 해주고
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;		//배열 탐색을 위한 카운트

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
	}
}


bool soundManager::isPlaySound(string keyName)
{
	bool isPlay;

	//이터레이터에 맵컨테이너 처음을 가르키게 해주고
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;		//배열 탐색을 위한 카운트

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool soundManager::isPauseSound(string keyName)
{
	bool isPause;

	//이터레이터에 맵컨테이너 처음을 가르키게 해주고
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;		//배열 탐색을 위한 카운트

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPaused(&isPause);
			break;
		}
	}

	return isPause;
}
