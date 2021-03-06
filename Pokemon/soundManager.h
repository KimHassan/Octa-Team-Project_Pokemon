#pragma once
#include "singletonBase.h"
#include <map>

#include "inc/fmod.hpp"//fmod.hpp 파일 인클루드
#pragma comment(lib, "lib/fmodex_vc.lib") //라이브러리 파일 등록

using namespace FMOD;

#define SOUNDBUFFER 1000
#define EXTRACHANNELBUFFER 5

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

class soundManager : public singletonBase<soundManager>
{
private:
	typedef map<string, Sound**>				arrSounds;
	typedef map<string, Sound**>::iterator		arrSoundsIter;
	typedef map<string, Channel**>				arrChannels;
	typedef map<string, Channel**>::iterator	arrChannelsIter;

private:
	System * _system;
	Sound** _sound;
	Channel** _channel;

	//맵 컨테이너(사운드를 담을)
	arrSounds _mTotalSounds;

public:
	soundManager();
	~soundManager();

	HRESULT init();
	void release();
	void update();

	void addSound(string keyName, string soundName, bool bgm, bool loop);

	//0 ~ 255 -> 0.0 ~ 1.0f
	void play(string keyName, float volume = 1.0f);
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);
};

