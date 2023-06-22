#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <intrin.h>
#include "matr.h"
#include "arr.h"
#include <statistic.h>

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
	return f1_time;
}

uint64_t f2(void)
{
	Array_Fill(A);
	f2_time = __rdtsc();
	Array_Sort(A);
	f2_time = -__rdtsc();
	return f2_time;
}

uint64_t f3(void)
{
	Matr_Rand(M1);
	Matr_Rand(M2);
	f3_time = __rdtsc();
	Matr_Mul(M1, M2);
	f3_time = -__rdtsc();
	return f3_time;
}

uint64_t ff(void)
{
	f1();
	if (rnd1f() <= 0.5f)
		f2();
	else
		f3();
	ff_time = f1_time + f2_time + f3_time;
	return ff_time;
}

int main(void)
{
	f_index = 0;
	A = Array_New(1000);
	M1 = Matr_NewSq(100);
	M2 = Matr_NewSq(100);
	for (f_index = 0; f_index < 100; f_index++)
		ff();
	float
		t1 = Stat_avgu64(times[0], 100),
		t2 = Stat_avgu64(times[1], 100),
		t3 = Stat_avgu64(times[2], 100),
		ts = Stat_avgu64(times[3], 100);
	float
		* tim1 = Stat_ticksToTime(times[0], 100, 3.0e9),
		* tim2 = Stat_ticksToTime(times[1], 100, 3.0e9),
		* tim3 = Stat_ticksToTime(times[2], 100, 3.0e9),
		* timF = Stat_ticksToTime(times[3], 100, 3.0e9);
	for (size_t i = 0; i < 100; i++)
	{
		printf("%1.8e\t%1.8e\t%1.8e\t%1.8e\n",
			tim1[i], tim2[i], tim3[i], timF[i]);
		/*printf("%011u\t%011u\t%011u\t%011u\n",
			times[0][i], times[1][i], times[2][i], times[3][i]);*/
	}
	free(tim1);
	free(tim2);
	free(tim3);
	free(timF);
	Matr_Delete(M1);
	Matr_Delete(M2);
	Array_Delete(A);
	return 0;
}