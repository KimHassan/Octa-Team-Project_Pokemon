#pragma once
//=====================================
// ## 18.01.31 ## - image Class - ##
//=====================================

#include "animation.h"

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,		//이미지를 리소스 파일로 부터...
		LOAD_FILE,			//이미지를 파일로 부터...
		LOAD_EMPTY,			//빈 비트맵 이미지를 사용시
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD		resID;		//리소스 불러올때 ID넘버
		HDC			hMemDC;		//DC
		HBITMAP		hBit;		//비트맵 이미지
		HBITMAP		hOBit;
		float		x;
		float		y;
		int			width;		//가로크기
		int			height;		//세로크기

		int			currentFrameX;	//현재 프레임 번호 X
		int			currentFrameY;	//현재 프레임 번호 Y
		int			maxFrameX;		//최대 프레임 장 수 (가로)
		int			maxFrameY;		//최대 프레임 장 수 (세로)
		int			frameWidth;		//프레임 가로크기
		int			frameHeight;	//프레임 세로크기
		BYTE		loadType;	//불러올 이미지 타입

		tagImageInfo()
		{
			resID		= 0;
			hMemDC		= NULL;
			hBit		= NULL;
			hOBit		= NULL;
			x			= 0;
			y			= 0;
			width		= 0;
			height		= 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX		= 0;
			maxFrameY		= 0;
			frameWidth		= 0;
			frameHeight		= 0;

			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//이미지 정보
	CHAR*			_fileName;		//파일 이름
	BOOL			_trans;			//특정칼라 값 제거 여부
	COLORREF		_transColor;	//어떤 칼라를 제거할꺼냐

	BLENDFUNCTION	_blendFunc;		//알파블렌드 함수
	LPIMAGE_INFO	_blendImage;	//알파블렌드 이미지

public:
	image();
	~image();

	//이미지 초기화
	HRESULT init(int width, int height);
	HRESULT init(const char* fileName, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);
	HRESULT init(const char* fileName, float x, float y, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);

	HRESULT init(const char* fileName, float x, float y, int width, int height,
		int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE);
	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY,
		BOOL trans = FALSE, COLORREF transColor = FALSE);

	//이미지 해제
	void release(void);

	void setTransColor(BOOL trans, COLORREF transColor);

	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void scaleRender(HDC hdc, int destX, int destY, int scaleX, int scaleY);
	void scaleRender(HDC hdc, int destX, int destY, int sourX, int sourY, 
					int sourWidth, int sourHeight, int scaleX, int scaleY);

	//루프렌더       그릴DC   그려줄 영역,            루프 방향 X   루프 방향 Y
	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	void frameAlphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	void aniRender(HDC hdc, int destX, int destY, animation* ani);
	void aniScaleRender(HDC hdc, int destX, int destY, int scaleX, int scaleY, animation* ani);

	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	//====================================================
	// ## 이미지 사용 편의를 위한 접근자, 설정자 ##
	//====================================================

	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX() { return _imageInfo->x; }

	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY() { return _imageInfo->y; }

	inline void setCenter(float x, float y)
	{
		//만약에 프레임번호에 정보가 있다면 프레임이미지인데?!
		//은재가 반친구들을 위해 예외처리 해주어요
		_imageInfo->x = x - _imageInfo->width / 2;
		_imageInfo->y = y - _imageInfo->height / 2;
	}

	inline float getCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ? _imageInfo->x + (_imageInfo->width / 2) : _imageInfo->x + (_imageInfo->frameWidth / 2);
	}
	inline float getCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ? _imageInfo->y + (_imageInfo->height / 2) : _imageInfo->y + (_imageInfo->frameHeight / 2);
	}

	inline int getWidth() { return _imageInfo->width; }
	inline int getHeight() { return _imageInfo->height; }

	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }

	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline int getFrameY() { return _imageInfo->currentFrameY; }

	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }

};

