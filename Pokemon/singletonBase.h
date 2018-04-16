#pragma once

template <typename T>
class singletonBase
{
protected:
	static T* singleton;

	singletonBase(){};
	~singletonBase(){};

public:
	//�̱��� ������
	static T* getSingleton(void);

	//�̱��� ����
	void releaseSingleton(void);
};

//�̱��� �ʱ�ȭ
template <typename T>
T* singletonBase<T>::singleton = 0;

//�̱��� ���� �Լ�
template <typename T>
T* singletonBase<T>::getSingleton()
{
	//�̱����� �Ǿ������ʴٸ�
	if (!singleton) singleton = new T;

	return singleton;
}

template <typename T>
void singletonBase<T>::releaseSingleton()
{
	if (singleton)
	{
		delete singleton;

		singleton = 0;
	}
}