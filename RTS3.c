#include <Windows.h>
#include <locale.h>
#include <stdio.h>
#include <math.h>

HANDLE t_in, t_out, r_in, r_out;
CRITICAL_SECTION cs[3];

#define sqr_cs	cs[0]
#define sum_cs	cs[1]
#define sqrt_cs	cs[2]

DWORD WINAPI sqr_t(LPVOID lpParam)
{
	UNREFERENCED_PARAMETER(lpParam);
	double a;
	DWORD readed;
	while (t_in != NULL)
	{
		EnterCriticalSection(&sqr_cs);
		ReadFile(t_in, &a, sizeof(a), &readed, FALSE);
		if (readed != sizeof(a))
		{
			LeaveCriticalSection(&sqr_cs);
			continue;
		}
		a = a * a;
		WriteFile(r_out, &a, sizeof(a), &readed, FALSE);
		LeaveCriticalSection(&sqr_cs);
		while (sqr_cs.OwningThread == 0);
	}
	ExitThread(0);
}

DWORD WINAPI sum_t(LPVOID lpParam)
{
	UNREFERENCED_PARAMETER(lpParam);
	double a, b;
	DWORD readed;
	while (t_in != NULL)
	{
		EnterCriticalSection(&sum_cs);
		ReadFile(t_in, &a, sizeof(a), &readed, FALSE);
		if (readed != sizeof(a))
		{
			LeaveCriticalSection(&sum_cs);
			continue;
		}
		ReadFile(t_in, &b, sizeof(b), &readed, FALSE);
		if (readed != sizeof(b))
		{
			LeaveCriticalSection(&sum_cs);
			continue;
		}
		a = a + b;
		WriteFile(r_out, &a, sizeof(a), &readed, FALSE);
		LeaveCriticalSection(&sum_cs);
		while (sum_cs.OwningThread == 0);
	}
	ExitThread(0);
}
DWORD WINAPI sqrt_t(LPVOID lpParam)
{
	UNREFERENCED_PARAMETER(lpParam);
	double a;
	DWORD readed;
	while (t_in != NULL)
	{
		EnterCriticalSection(&sqrt_cs);
		ReadFile(t_in, &a, sizeof(a), &readed, FALSE);
		if (readed != sizeof(a))
		{
			LeaveCriticalSection(&sqrt_cs);
			continue;
		}
		a = sqrt(a);
		WriteFile(r_out, &a, sizeof(a), &readed, FALSE);
		LeaveCriticalSection(&sqrt_cs);
		while (sqrt_cs.OwningThread == 0);
	}
	ExitThread(0);
}

int main(void)
{
	InitializeCriticalSection(&cs[0]);
	InitializeCriticalSection(&cs[1]);
	InitializeCriticalSection(&cs[2]);
	EnterCriticalSection(&sum_cs);
	EnterCriticalSection(&sqr_cs);
	EnterCriticalSection(&sqrt_cs);
	CreatePipe(&t_in, &t_out, NULL, 0);
	CreatePipe(&r_in, &r_out, NULL, 0);
	DWORD tid;
	HANDLE hThread[3];
	setlocale(LC_ALL, "rus");
	hThread[0] = CreateThread(0, 0, sqr_t,	NULL, 0, &tid);
	printf("Поток 0x%x создан\n", tid);
	hThread[1] = CreateThread(0, 0, sum_t,	NULL, 0, &tid);
	printf("Поток 0x%x создан\n", tid);
	hThread[2] = CreateThread(0, 0, sqrt_t,	NULL, 0, &tid);
	printf("Поток 0x%x создан\n", tid);
	DWORD readed;


	printf("ВВедите длины катетов, разделяя их пробелом или переносом сторки\n");
	double a = 2, b = 4;
	scanf_s("%lf %lf", &a, &b);

	printf("a = %lf\n", a);
	LeaveCriticalSection(&sqr_cs);
	while (sqr_cs.OwningThread == 0);
	WriteFile(t_out, &a, sizeof(a), &readed, FALSE);
	EnterCriticalSection(&sqr_cs);

	ReadFile(r_in, &a, sizeof(a), &readed, FALSE);
	printf("a2 = %lf\n", a);

	printf("b = %lf\n", b);
	LeaveCriticalSection(&sqr_cs);
	while (sqr_cs.OwningThread == 0);
	WriteFile(t_out, &b, sizeof(b), &readed, FALSE);
	EnterCriticalSection(&sqr_cs);

	ReadFile(r_in, &b, sizeof(a), &readed, FALSE);
	printf("b2 = %lf\n", b);

	LeaveCriticalSection(&sum_cs);
	while (sum_cs.OwningThread == 0);
	WriteFile(t_out, &a, sizeof(a), &readed, FALSE);
	WriteFile(t_out, &b, sizeof(b), &readed, FALSE);
	EnterCriticalSection(&sum_cs);

	ReadFile(r_in, &a, sizeof(a), &readed, FALSE);
	printf("sum = %lf\n", a);

	LeaveCriticalSection(&sqrt_cs);
	while (sqrt_cs.OwningThread == 0);
	WriteFile(t_out, &a, sizeof(a), &readed, FALSE);
	EnterCriticalSection(&sqrt_cs);

	ReadFile(r_in, &a, sizeof(a), &readed, FALSE);
	printf("sqrt = %lf\n", a);

	DeleteCriticalSection(&cs[0]);
	DeleteCriticalSection(&cs[1]);
	DeleteCriticalSection(&cs[2]);
	TerminateThread(hThread[0], 0);
	TerminateThread(hThread[1], 0);
	TerminateThread(hThread[2], 0);
	CloseHandle(t_in);
	CloseHandle(t_out);
	CloseHandle(r_in);
	CloseHandle(r_out);
	system("pause");
	return 0;
}