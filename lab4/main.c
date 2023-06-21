#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <intrin.h>
#include "matr.h"
#include "arr.h"

// BDFGJ
/*
			+---> [2]-+
 [1] -> <r<0.5>		  +->
			+---> [3]-+
*/


#define f1_time times[0][f_index]
#define f2_time times[1][f_index]
#define f3_time times[2][f_index]
#define ff_time times[3][f_index]

typedef uint64_t frag(void);

float rnd1f() {
	return  (float)rand() / RAND_MAX;
}

arr A;
matr M1, M2;
uint64_t times[4][100];
uint16_t f_index;

uint64_t f1(void)
{
	f1_time = __rdtsc();
	uint32_t num = 614657;
	for (uint32_t num = 614657; num > 1;)
	{
		uint32_t diver = 2;
		for (; num % diver != 0; diver++);
		num /= diver;	
	}

	f1_time = -__rdtsc();
}

uint64_t f2(void)
{
	Array_Fill(A);
	f2_time = __rdtsc();
	Array_Sort(A);
	f2_time = -__rdtsc();
}

uint64_t f3(void)
{
	Matr_Rand(M1);
	Matr_Rand(M2);
	f3_time = __rdtsc();
	Matr_Mul(M1, M2);
	f3_time = -__rdtsc();
}

uint64_t ff(void)
{
	f1();
	if (rnd1f() <= 0.5f)
		f2();
	else
		f3();
	ff_time = f1_time + f2_time + f3_time;
}

float avg(uint64_t* arr, size_t len)
{
	float ret = 0;
	for (size_t i = 0; i < len; i++)
		ret += arr[i];
	ret /= len;
	return ret;
}

float Array_minf(float* A, uint16_t len)
{
	if (len < 1)
		return A[0];
	float R = A[0];
	for (size_t i = 1; i < len; i++)
	{
		if (A[i] < R)
			R = A[i];
	}
	return R;
}


float Array_maxf(float* A, uint16_t len)
{
	if (len < 1)
		return A[0];
	float R = A[0];
	for (size_t i = 1; i < len; i++)
	{
		if (A[i] > R)
			R = A[i];
	}
	return R;
}

void norm(float* A, uint16_t len)
{
	float max = Array_maxf(A, len);
	float min = Array_minf(A, len);
	float q = max - min;

	for (size_t i = 0; i < len; i++)
		A[i] = (A[i] - min) / q;
}

void hist(float* A, uint16_t len, uint8_t cnt)
{
	float min = Array_minf(A, len);
	float max = Array_maxf(A, len);
	float divid = (max - min) / cnt;

	uint8_t* ret = (uint8_t*)calloc(cnt, sizeof(uint8_t));
	float Ax = min, Bx = min + divid;
	for (size_t i = 0; i < cnt; i++)
	{
		printf("%2.2e ", Ax + 0.5f * divid - min);
		ret[i] = 0;
		for (size_t j = 0; j < len; j++)
		{
			if (Ax <= A[j] && A[j] < Bx)
			{
				printf("#");
				ret[i] ++;
			}
		}
		printf("\r\n");
		Ax += divid;
		Bx += divid;
	}
	
	free(ret);
}
// 27669979496244576256.000000
int main(void)
{
	f_index = 0;
	A = Array_New(1000);
	M1 = Matr_NewSq(100);
	M2 = Matr_NewSq(100);
	for (f_index = 0; f_index < 100; f_index++)
		ff();
	float
		t1 = avg(times[0], 100),
		t2 = avg(times[1], 100),
		t3 = avg(times[2], 100),
		ts = avg(times[3], 100);
	hist(times[3], 100, 8);
	printf(
		"f1:	%22.0f\n"
		"f2:	%22.0f\n"
		"f3:	%22.0f\n"
		"sumf:	%22.0f\n"
		" = :	%22.0f\n",
		t1, t2, t3, ts, t1 + 0.5*t2 + 0.5*t3
	);
	for (size_t i = 0; i < 100; i++)
	{
		printf("%016lu\t%016lu\t%016lu\t%016lu\n",
			times[0][i], times[1][i], times[2][i], times[3][i]);
	}
	Matr_Delete(M1);
	Matr_Delete(M2);
	Array_Delete(A);
	return 0;
}