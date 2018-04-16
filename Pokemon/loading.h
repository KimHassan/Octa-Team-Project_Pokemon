#pragma once
#include "gameNode.h"
#include "progressBar.h"

enum LOAD_KIND
{
	LOAD_KIND_IMAGE_0,			//�̹��� �ʱ�ȭ ��� 1
	LOAD_KIND_IMAGE_1,			//�̹��� �ʱ�ȭ ��� 2
	LOAD_KIND_IMAGE_2,			//�̹��� �ʱ�ȭ ��� 3
	LOAD_KIND_FRAMEIMAGE_0,		//�������̹��� �ʱ�ȭ ��� 1
	LOAD_KIND_FRAMEIMAGE_1,		//�������̹��� �ʱ�ȭ ��� 2
	LOAD_KIND_SOUND,			//���� �߰� ���
	LOAD_KIND_END
};

struct tagImageResource
{
	string keyName;			//�̹��� Ű ��
	const char* fileName;	//���� �̸�
	float x, y;				//��ǥ
	int width, height;		//����,���� ũ��
	int frameX, frameY;		//�����ӹ�ȣ
	bool trans;				//�÷��� �������� ����
	COLORREF transColor;
};

class loadItem
{
private:
	LOAD_KIND			_kind;
	tagImageResource	_imageResource;

public:
	loadItem();
	~loadItem();

	HRESULT initForImage(string keyName, int width, int height);
	HRESULT initForImage(string keyName, const char* fileName, int width, int height, BOOL trans = FALSE,
		COLORREF transColor = FALSE);
	HRESULT initForImage(string keyName, const char* fileName, float x, float y, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);
	HRESULT initForFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE);
	HRESULT initForFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE);

	LOAD_KIND getLoadingKind() { return _kind; }

	tagImageResource getImageResource() { return _imageResource; }

	

};

class loading : public gameNode
{
private:
	typedef vector<loadItem*>			arrLoadItem;
	typedef vector<loadItem*>::iterator arrLoadItemIter;

private:
	arrLoadItem _vLoadItem;
	image* _background;
	progressBar* _loadingBar;

	tagImageResource _imageResource;

	int _currentGauge;

	image* _mus;
	int _index;
	int _count;
	int _loadCount;

public:
	loading();
	~loading();

	HRESULT init();
	void release();
	void update();
	void render();

	//�̹��� �ε� ����
	void loadImage(string keyName, int width, int height);
	void loadImage(string keyName, const char* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE);
	void loadImage(string keyName, const char* fileName, float x, float y, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE);

	void loadFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE);
	void loadFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE);

	BOOL loadingDone();

	vector<loadItem*> getLoadItem() { return _vLoadItem; }

};

