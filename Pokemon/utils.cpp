#include "stdafx.h"
#include "utils.h"

namespace OCTA_UTIL
{
	//hypo ������
	float getDistance(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		return sqrtf(x * x + y * y);
	}

	//���� ������
	float getAngle(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		float distance = sqrtf(x * x + y * y);

		float angle = acosf(x / distance);

		//atan2f�� �ʿ���µ� acos�� �ʿ��ϴ�
		if (y2 > y1)
		{
			angle = PI2 - angle;

			if (angle >= PI2) angle -= PI2;
		}

		return angle;
	}

}