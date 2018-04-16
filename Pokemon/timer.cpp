#include "stdafx.h"
#include "timer.h"
#include <mmsystem.h>  //timeGetTime()

#pragma comment(lib, "winmm.lib")
	

timer::timer()
{
}


timer::~timer()
{
}

//MIRC  irc

HRESULT timer::init(void)
{

	if ( QueryPerformanceFrequency((LARGE_INTEGER*) &_periodFrequency) )
	{
		_isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*) &_lastTime);

		_timeScale = 1.0f / _periodFrequency;
	}
	else
	{
		_isHardware = false;

		_lastTime = timeGetTime();	//강제로 밀리세컨으로 맞춘다 0.001
		_timeScale = 0.001f;
	}

	_frameRate = 0;
	_FPSframeCount = 0;
	_FPStimeElapsed = 0;
	_worldTime = 0;

	return S_OK;
}

void timer::tick(float lockFPS)
{
	if ( _isHardware )
	{
		QueryPerformanceCounter((LARGE_INTEGER*) &_curTime);
	}
	else
	{
		_curTime = timeGetTime();
	}

	//틱카운트를 구해봅시다
	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	//프레임 스키핑이라고 부름 고정 프레임
	if ( lockFPS > 0.0f )
	{
		while ( _timeElapsed < (1.0f / lockFPS) )
		{
			if ( _isHardware)  QueryPerformanceCounter((LARGE_INTEGER*) &_curTime);
			else _curTime = timeGetTime();

			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}

	//시간 갱신
	_lastTime = _curTime;
	//프레임카운트  -> 화면에 뿌릴 60FPS 
	_FPSframeCount++;
	_FPStimeElapsed += _timeElapsed;

	//컴파일되고 흐른 총 시간 (월드타임)
	_worldTime += _timeElapsed;

	if ( _FPStimeElapsed > 1.0f )
	{
		_frameRate = _FPSframeCount;
		_FPSframeCount = 0;
		_FPStimeElapsed = 0.0f;
	}

}

unsigned long timer::getFrameRate(char* str) const
{
	if ( str != NULL )
	{
		wsprintf(str, "FPS : %d", _frameRate);
	}

	return _frameRate;
}