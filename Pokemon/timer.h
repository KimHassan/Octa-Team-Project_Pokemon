#pragma once
class timer
{
private:
	bool _isHardware;		//하드웨어가 고성능을 지원하는지 여부
	float _timeScale;		//FPS빈도
	float _timeElapsed;		//tick count;

	__int64 _curTime;
	__int64 _lastTime;
	__int64 _periodFrequency;

	unsigned long _frameRate;
	unsigned long _FPSframeCount;

	float _FPStimeElapsed;
	float _worldTime;

public:
	timer();
	~timer();

	HRESULT init(void);
	void tick(float lockFPS = 0.0f);
	unsigned long getFrameRate(char* str = NULL) const;

	inline float getElapsedTime(void) const { return _timeElapsed; }
	inline float getWorldTime(void) const { return _worldTime; }

};

