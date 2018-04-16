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
	_background = IMAGEMANAGER->addImage("로딩백그라운드", "image/메이플타이틀.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_loadingBar = new progressBar;
	_loadingBar->init("image/loadingBarTop", "image/loadingBarBottom", WINSIZEX / 2, WINSIZEY - 20, WINSIZEX, 20);
	_loadingBar->setGauge(0, 0);

	_currentGauge = 0;

	_mus = IMAGEMANAGER->addFrameImage("버섯", "image/로딩버섯.bmp", 388, 91, 4, 1, true, RGB(255, 0, 255));
	//-- 버섯이미지 추가한부분 좌표셋팅
	//-- 좌표가 로딩게이지바 width이면 맨오른쪽 끝이겠지? 거기에서 버섯이미지사이즈만큼을 뺀다면
	//-- 게이지바 바로옆에 버섯이있겟지
	//-- 우선 get함수 잘모르겠으면 클릭해서 따라가던지 2DGameFrameWork들어가서
	//-- ProgressBar 헤더파일 ㄱㄱ
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

	//-- 업데이트에도 넣어줘야 계속 따라가겠지?
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
	//-- _vLoadItem인 이유가 위에 itemResource.fileName의 값을
	//-- 로딩씬에서 loadImage()에 담는데 담는 수만큼 벡터로 담아버리는데
	//-- 이미지가 한개지만 이미 for문으로 예를들어 로딩씬에 400개를 돌리면
	//-- 이미지를 400개를 추가했다는 뜻이야. 그렇기 때문에 로드이미지를 400번 만들었으니
	//-- 벡터에도 400개가되겠지? 그럼 _vLoadItem(벡터)에 담겨있는 배열의 갯수는 400개가 될테니
	//-- 여기 아래 for문에서도 _vLoadItem(벡터) 최대사이즈만큼 돌려버리고 해당 배열에 추가된 fileName을넣으면
	//-- 각 백터배열에 넣어놓은 fileName을 불러오는데 솔직히 지금 이미지 1장이다보니 이름이 계속 똑같게나와
	//-- 그래서 갯수확인하기위해서 _currentGauge를 넣은거임ㅇㅇ _currentGauge가 
	//--  현재 게이지 갯수니 걍 이렇게 하면됨
	for (int i = 0; i < _vLoadItem.size(); i++)
	{
		sprintf_s(str, "%s%d", _vLoadItem[i]->getImageResource().fileName, _currentGauge);
		TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY - 50, str, strlen(str));
	}
}


//이미지 로딩 종류
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
	//로딩이 끝나면 끝났다고 알려줘라
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
