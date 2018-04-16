#pragma once
#include <vector>

//void* - ���̵� �����Ͷ�?
//� ���µ��� �� ����ų���ִ�(�ڷ����� ���ֹ��� �ʰ� �� �������ִ�)
//������ �޾ƿ� ���̵������Ϳ� ���� �������ϴ� �ڷ����� ĳ������ ������Ѵ�

typedef void(*CALLBACK_FUNCTION)(void);
typedef void(*CALLBACK_FUNCTION_PARAMETER)(void*);

class animation
{
public:
	typedef vector<POINT>	vFrameList;	//������ ��ȣ ��ġ
	typedef vector<int>		vPlayList;	//�ִϸ��̼� �÷��̸���Ʈ ��ȣ

private:
	int			_frameNum;		//�������� �� ����
	vFrameList	_frameList;		//������ ����Ʈ
	vPlayList	_playList;		//�÷��� ����Ʈ

	int			_frameWidth;	//������ ����ũ��
	int			_frameHeight;	//������ ����ũ��

	BOOL		_loop;					//�ִϸ��̼� ���� ����

	float		_frameUpdateSec;		//������ ������Ʈ��
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

	//����Ʈ �ִϸ��̼� ���
	void setDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//�迭�� �ִϸ��̼� ���
	void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//���� ���ؼ� �ִϸ��̼� ���(3 ~ 7)
	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//�ִϸ��̼� ������ ����
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

