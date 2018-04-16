#include "stdafx.h"
#include "backBuffer.h"

//��� �̴ϼȶ�����
//�����ڴ� ��ü�� �����Ǹ鼭 �ڵ����� ����Ǵ� ���̱� ������
//�̰��� �ʱ�ȭ�� �صθ� Ŭ������ �Ҵ縸�ص� �ʱ�ȭ�� �� ���ִ�
//������ const �Ӽ� ��� ���� ��ü �θ��鼭 �ʱ�ȭ�� �� �� �Ϸ���
//������� �����ε� ���ؼ� �׳� �ʱ�ȭ�뵵�ε� ���� ����

backBuffer::backBuffer()
	: _backBufferInfo(NULL)
{
}


backBuffer::~backBuffer()
{

}

HRESULT backBuffer::init(int width, int height)		  
{
	//���� ����ۿ� ������ ���������� == �ʱ�ȭ ���� �ʾҴٸ�
	if (_backBufferInfo != NULL) release(); 

	HDC hdc = GetDC(_hWnd);

	_backBufferInfo = new backBuffer_INFO;
	_backBufferInfo->hMemDC = CreateCompatibleDC(hdc);	//�� DC������ ����
	_backBufferInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);	//ũ�� ��ŭ�� �� ��Ʈ�� �̹��� ����
	_backBufferInfo->hOBit = (HBITMAP)SelectObject(_backBufferInfo->hMemDC, _backBufferInfo->hBit);
	_backBufferInfo->width = width;
	_backBufferInfo->height = height;

	//�� ��Ʈ�� �̹����� �������� �ʾҴٸ�
	if (_backBufferInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	//<assert> -> assert("false����", "����");

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
	//����ۿ� �ִ� �� ������ ��Ӻ��� ���ִ� �Լ�
	BitBlt(hdc, destX, destY,
		_backBufferInfo->width, _backBufferInfo->height,
		_backBufferInfo->hMemDC, 0, 0, SRCCOPY);
}
