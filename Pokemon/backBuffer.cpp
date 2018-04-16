#include "stdafx.h"
#include "backBuffer.h"

//멤버 이니셜라이즈
//생성자는 객체가 생성되면서 자동으로 실행되는 곳이기 떄문에
//이곳에 초기화를 해두면 클래스를 할당만해도 초기화를 할 수있다
//원래는 const 속성 상수 값을 객체 부르면서 초기화를 한 번 하려고
//만들어진 문법인데 편해서 그냥 초기화용도로도 많이 쓴다

backBuffer::backBuffer()
	: _backBufferInfo(NULL)
{
}


backBuffer::~backBuffer()
{

}

HRESULT backBuffer::init(int width, int height)		  
{
	//뭔가 백버퍼에 정보가 남아있으면 == 초기화 되지 않았다면
	if (_backBufferInfo != NULL) release(); 

	HDC hdc = GetDC(_hWnd);

	_backBufferInfo = new backBuffer_INFO;
	_backBufferInfo->hMemDC = CreateCompatibleDC(hdc);	//빈 DC영역을 생성
	_backBufferInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);	//크기 만큼의 빈 비트맵 이미지 생성
	_backBufferInfo->hOBit = (HBITMAP)SelectObject(_backBufferInfo->hMemDC, _backBufferInfo->hBit);
	_backBufferInfo->width = width;
	_backBufferInfo->height = height;

	//빈 비트맵 이미지가 생성되지 않았다면
	if (_backBufferInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	//<assert> -> assert("false조건", "유언");

	ReleaseDC(_hWnd, hdc);

	return 0;
}

void backBuffer::release(void)						  
{
	if (_backBufferInfo)
	{
		SelectObject(_backBufferInfo->hMemDC, _backBufferInfo->hOBit);
		DeleteObject(_backBufferInfo->hBit);
		DeleteDC(_backBufferInfo->hMemDC);

		delete _backBufferInfo;
		_backBufferInfo = 0;
	}
}

void backBuffer::render(HDC hdc, int destX, int destY)
{
	//백버퍼에 있는 걸 앞으로 고속복사 해주는 함수
	BitBlt(hdc, destX, destY,
		_backBufferInfo->width, _backBufferInfo->height,
		_backBufferInfo->hMemDC, 0, 0, SRCCOPY);
}
