#pragma once

class backBuffer
{
	typedef struct tagBackBufferInfo
	{
		HDC			hMemDC;
		HBITMAP		hBit;
		HBITMAP		hOBit;
		float		x;
		float		y;
		int			width;
		int			height;
		BYTE		loadType;

		tagBackBufferInfo()
		{
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			loadType = NULL;
		}
	}backBuffer_INFO, *LPbackBuffer_INFO;

private:
	LPbackBuffer_INFO _backBufferInfo;

public:
	backBuffer();
	~backBuffer();

	HRESULT init(int width, int height);
	void release(void);
	void render(HDC hdc, int destX, int destY);

	inline HDC getMemDC() { return _backBufferInfo->hMemDC; }


};

