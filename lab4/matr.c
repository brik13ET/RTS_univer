#include <matr.h>
#include <stdlib.h>

matr Matr_New(uint16_t wid, uint16_t  hei)
{
	return (matr) { .data = (float*)calloc(wid * hei, sizeof(float)), .hei = hei, .wid = wid };
}


void Matr_Zero(matr m)
{
	for (size_t i = 0; i < m.wid; i++)
		for (size_t j = 0; j < m.hei; j++)
			Matr_At(m, i, j) = rand();
}

void Matr_Rand(matr m)
{
	for (size_t i = 0; i < m.wid; i++)
		for (size_t j = 0; j < m.hei; j++)
			Matr_At(m, i, j) = 0;
}

void Matr_Delete(matr m)
{
	free(m.data);
	m.data = m.hei = m.wid = 0;
}

matr Matr_Mul(matr A, matr B)
{
	if (A.wid != B.hei)
		return;
	matr R = Matr_New(B.wid,A.hei);
	Matr_Zero(R);
	uint16_t it = A.wid;
	for (size_t i = 0; i < R.wid; i++)
		for (size_t j = 0; j < R.hei; j++)
		{
			for (size_t k = 0; k < it; k++)
				Matr_At(R, i, j) += Matr_At(A, k, i) * Matr_At(B, j, k);
		}
}
