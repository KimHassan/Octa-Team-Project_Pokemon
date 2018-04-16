#pragma once
#include <vector>

//void* - 보이드 포인터란?
//어떤 형태든지 다 가르킬수있다(자료형에 구애받지 않고 다 담을수있다)
//단점은 받아온 보이드포인터에 내가 쓰고자하는 자료형을 캐스팅을 해줘야한다

typedef void(*CALLBACK_FUNCTION)(void);
typedef void(*CALLBACK_FUNCTION_PARAMETER)(void*);

class animation
{
public:
	typedef vector<POINT>	vFrameList;	//프레임 번호 위치
	typedef vector<int>		vPlayList;	//애니메이션 플레이리스트 번호

private:
	int			_frameNum;		//프레임이 몇 개냐
	vFrameList	_frameList;		//프레임 리스트
	vPlayList	_playList;		//플레이 리스트

	int			_frameWidth;	//프레임 가로크기
	int			_frameHeight;	//프레임 세로크기

	BOOL		_loop;					//애니메이션 루프 여부

	float		_frameUpdateSec;		//프레임 업데이트용
	float		_elapsedSec;

	DWORD		_nowPlayIndex;
	BOOL		_play;

	void*							_obj;
	CALLBACK_FUNCTION				_callbackFunction;
	CALLBACK_FUNCTION_PARAMETER		_callbackFunctionParameter;

public:
	animation();
	~animation();

	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release();

	//디폴트 애니메이션 재생
	void setDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//배열로 애니메이션 재생
	void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//구간 정해서 애니메이션 재생(3 ~ 7)
	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//애니메이션 프레임 셋팅
	void setFPS(int framePerSec);


	void frameUpdate(float elapsedTime);

	void start();
	void stop();
	void pause();
	void resume();

	inline BOOL isPlay() { return _play; }
	inline POINT getFramePos() { return _frameList[_playList[_nowPlayIndex]]; }
	inline int getFrameWidth() { return _frameWidth; }
	inline int getFrameHeight() { return _frameHeight; }

};

