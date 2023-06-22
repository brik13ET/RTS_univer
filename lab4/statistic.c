#include <statistic.h>
#include <stdlib.h>
#include <stdint.h>


float Stat_avgu64(uint64_t* arr, size_t len)
{
	float ret = 0;
	for (size_t i = 0; i < len; i++)
		ret += arr[i];
	ret /= len;
	return ret;
}

float Stat_minf(float* A, uint16_t len)
{
	if (len < 1)
		return 0;
	float R = A[0];
	for (size_t i = 1; i < len; i++)
	{
		if (A[i] < R)
			R = A[i];
	}
	return R;
}


float Stat_maxf(float* A, uint16_t len)
{
	if (len < 1)
		return 0;
	float R = A[0];
	for (size_t i = 1; i < len; i++)
	{
		if (A[i] > R)
			R = A[i];
	}
	return R;
}

void Stat_normf(float* A, uint16_t len)
{
	float max = Stat_maxf(A, len);
	float min = Stat_minf(A, len);
	float q = max - min;

	for (size_t i = 0; i < len; i++)
		A[i] = (A[i] - min) / q;
}

void Stat_histf(float* A, uint16_t len, uint8_t cnt)
{
	float min = Stat_minf(A, len);
	float max = Stat_maxf(A, len);
	float divid = (max - min) / cnt;

	uint8_t* ret = (uint8_t*)calloc(cnt, sizeof(uint8_t));
	uint8_t cnt2 = cnt, ind = 0;
	float Ax = min, Bx = min + divid;
	while (cnt2 > 0)
	{
		ret[ind] = 0;
		for (size_t j = 0; j < len; j++)
		{
			if (Ax <= A[j] && A[j] < Bx)
			{
				ret[ind] = 0;
				ind++;
				cnt2--;
			}
		}
	}

	free(ret);
}

float* Stat_ticksToTime(uint64_t* A, uint16_t len, float Freq)
{
	float* ret = (float*)calloc(len, sizeof(Freq));
	for (size_t i = 0; i < len; i++)
	{
		ret[i] = (float)A[i] / Freq;
	}
	return ret;
}
