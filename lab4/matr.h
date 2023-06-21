#ifndef MATR_H
#define MATR_H

#include <arr.h>

typedef struct
{
	float* data;
	uint16_t wid;
	uint16_t hei;
} matr;
#define Matr_NewSq(s) Matr_New(s,s)
#define Matr_At(M,i,j) M.data[M.wid * j + i]

matr Matr_New(uint16_t wid, uint16_t  hei);
void Matr_Zero(matr);
void Matr_Rand(matr);
matr Matr_Mul(matr, matr);
void Matr_Delete(matr);

#endif 