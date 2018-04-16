#include "stdafx.h"
#include "loading.h"

loadItem::loadItem(){}
loadItem::~loadItem(){}

HRESULT loadItem::initForImage(string keyName, int width, int height)
{
	_kind = LOAD_KIND_IMAGE_0;

	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char* fileName, int width, int height, BOOL trans,
	COLORREF transColor)
{
	_kind = LOAD_KIND_IMAGE_1;

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char* fileName, float x, float y, int width, int height,
	BOOL trans, COLORREF transColor)
{
	_kind = LOAD_KIND_IMAGE_2;

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	_kind = LOAD_KIND_FRAMEIMAGE_1;

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}




loading::loading()
{
}


loading::~loading()
{

}

HRESULT loading::init()
{
	_background = IMAGEMANAGER->addImage("�ε���׶���", "image/������Ÿ��Ʋ.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_loadingBar = new progressBar;
	_loadingBar->init("image/loadingBarTop", "image/loadingBarBottom", WINSIZEX / 2, WINSIZEY - 20, WINSIZEX, 20);
	_loadingBar->setGauge(0, 0);

	_currentGauge = 0;

	_mus = IMAGEMANAGER->addFrameImage("����", "image/�ε�����.bmp", 388, 91, 4, 1, true, RGB(255, 0, 255));
	//-- �����̹��� �߰��Ѻκ� ��ǥ����
	//-- ��ǥ�� �ε��������� width�̸� �ǿ����� ���̰���? �ű⿡�� �����̹��������ŭ�� ���ٸ�
	//-- �������� �ٷο��� �������ְ���
	//-- �켱 get�Լ� �߸𸣰����� Ŭ���ؼ� ���󰡴��� 2DGameFrameWork����
	//-- ProgressBar ������� ����
	_mus->setX(_loadingBar->getWidth() - _mus->getFrameWidth());
	_mus->setY(WINSIZEY - 150);
	_mus->setFrameX(0);
	_mus->setFrameY(0);
	_index = 0;
	_count = 0;
	_loadCount = 0;

	return S_OK;
}

void loading::release()
{
	SAFE_DELETE(_loadingBar);
}

void loading::update() 
{
	_loadingBar->update();

	//-- ������Ʈ���� �־���� ��� ���󰡰���?
	_mus->setX(_loadingBar->getWidth() - _mus->getFrameWidth());
	_mus->setY(WINSIZEY - 105);

	_count++;
	if (_count % 5 == 0)
	{
		_index++;
		_mus->setFrameX(_index);
		if (_index == 4) _index = 0;
		_count = 0;
	}
	_loadCount++;
}

void loading::render() 
{
	_background->render(getMemDC());
	_loadingBar->render();
	_mus->frameRender(getMemDC(), _mus->getX(), _mus->getY());

	char str[1300];
	ZeroMemory(str, sizeof(str));
	//-- _vLoadItem�� ������ ���� itemResource.fileName�� ����
	//-- �ε������� loadImage()�� ��µ� ��� ����ŭ ���ͷ� ��ƹ����µ�
	//-- �̹����� �Ѱ����� �̹� for������ ������� �ε����� 400���� ������
	//-- �̹����� 400���� �߰��ߴٴ� ���̾�. �׷��� ������ �ε��̹����� 400�� ���������
	//-- ���Ϳ��� 400�����ǰ���? �׷� _vLoadItem(����)�� ����ִ� �迭�� ������ 400���� ���״�
	//-- ���� �Ʒ� for�������� _vLoadItem(����) �ִ�����ŭ ���������� �ش� �迭�� �߰��� fileName��������
	//-- �� ���͹迭�� �־���� fileName�� �ҷ����µ� ������ ���� �̹��� 1���̴ٺ��� �̸��� ��� �Ȱ��Գ���
	//-- �׷��� ����Ȯ���ϱ����ؼ� _currentGauge�� �������Ӥ��� _currentGauge�� 
	//--  ���� ������ ������ �� �̷��� �ϸ��
	for (int i = 0; i < _vLoadItem.size(); i++)
	{
		sprintf_s(str, "%s%d", _vLoadItem[i]->getImageResource().fileName, _currentGauge);
		TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY - 50, str, strlen(str));
	}
}


//�̹��� �ε� ����
void loading::loadImage(string keyName, int width, int height)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, width, height);

	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char* fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, width, height, trans, transColor);

	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char* fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, x, y, width, height, trans, transColor);

	_vLoadItem.push_back(item);
}


void loading::loadFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, width, height, frameX, frameY, trans, transColor);

	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, x, y, width, height, frameX, frameY, trans, transColor);

	_vLoadItem.push_back(item);
}


BOOL loading::loadingDone()
{
	//�ε��� ������ �����ٰ� �˷����
	if (_currentGauge >= _vLoadItem.size())
	{
		return true;
	}

	loadItem* item = _vLoadItem[_currentGauge];

	switch (item->getLoadingKind())
	{
		case LOAD_KIND_IMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.width, img.height);
		}
		break;

		case LOAD_KIND_IMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height, img.trans, img.transColor);
		}
		break;
		case LOAD_KIND_IMAGE_2:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.trans, img.transColor);
		}
		break;
		case LOAD_KIND_FRAMEIMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
		}
		break;
		case LOAD_KIND_FRAMEIMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
		}
		break;
		case LOAD_KIND_SOUND:
		{

		}
		break;
	}

	_loadingBar->setGauge(_currentGauge, _vLoadItem.size());
	_currentGauge++;

	return FALSE;
}
