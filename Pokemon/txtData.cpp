#include "stdafx.h"
#include "txtData.h"


txtData::txtData()
{
}


txtData::~txtData()
{

}

HRESULT txtData::init()
{
	return S_OK;
}

void txtData::release()
{

}


//Save
void txtData::txtSave(const char* saveFileName, vector<string> vStr)
{
	HANDLE file;

	char str[128];
	DWORD write;

	//속성값에, 붙인 것들을 str에 복사한다
	strncpy_s(str, 128, vectorArrayCombine(vStr), 126);

	file = CreateFile(saveFileName, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, 128, &write, NULL);
	CloseHandle(file);
}

//문자열들을 조합하는 함수
char* txtData::vectorArrayCombine(vector<string> vArray)
{
	//일단 버퍼는 128로 해두는데, 여러분이 나중에
	//속성이 들어오는 만큼 늘릴 수 있도록 고쳐도 무방합니다

	char str[128];

	ZeroMemory(str, sizeof(str));

	//100,200,50

	for ( int i = 0; i < vArray.size(); ++i )
	{
		strncat_s(str, 128, vArray[i].c_str(), 126);
		if ( i + 1 < vArray.size() ) strcat_s(str, ",");
	}

	return str;
}


//Load
vector<string> txtData::txtLoad(const char* loadFileName)
{
	HANDLE file;

	DWORD read;

	char str[128];

	file = CreateFile(loadFileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 128, &read, NULL);

	CloseHandle(file);

	return charArraySeparation(str);
}

vector<string> txtData::charArraySeparation(char charArray[])
{
	vector<string> vArray;

	char* temp;
	char* separator = ",";
	char* token;

	token = strtok(charArray, separator);
	vArray.push_back(token);

	while ( NULL != (token = strtok(NULL, separator)))
	{
		vArray.push_back(token);
	}

	return vArray;
}
