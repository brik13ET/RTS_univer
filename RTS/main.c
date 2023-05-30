#include <Windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


/*
потоки одного процесса
событи€
каналы
квадратное уравнение
*/

HANDLE events[7];
HANDLE pipes[6*2];
HANDLE threads[6];
DWORD threadIds[6];

#define ev_sum	events[0]
#define ev_sub	events[1]
#define ev_mul	events[2]
#define ev_div	events[3]
#define ev_sqr	events[4]
#define ev_sqrt	events[5]
#define ev_ready events[6]

#define pw_sum	pipes[0*2]
#define pw_sub	pipes[1*2]
#define pw_mul	pipes[2*2]
#define pw_div	pipes[3*2]
#define pw_sqr	pipes[4*2]
#define pw_sqrt	pipes[5*2]

#define pr_sum	pipes[0*2 + 1]
#define pr_sub	pipes[1*2 + 1]
#define pr_mul	pipes[2*2 + 1]
#define pr_div	pipes[3*2 + 1]
#define pr_sqr	pipes[4*2 + 1]
#define pr_sqrt	pipes[5*2 + 1]

#define ht_sum	threads[0]
#define ht_sub	threads[1]
#define ht_mul	threads[2]
#define ht_div	threads[3]
#define ht_sqr	threads[4]
#define ht_sqrt	threads[5]

DWORD WINAPI t_sum(_In_ LPVOID LpParam)
{
	UNREFERENCED_PARAMETER(LpParam);
	HANDLE ev = OpenEvent(EVENT_ALL_ACCESS, FALSE, TEXT("sum"));
	HANDLE evok = OpenEvent(EVENT_ALL_ACCESS, FALSE, TEXT("calculated"));
	double a, b;
	DWORD readed;
	while (ev != NULL)
	{
		readed = 0;
		DWORD dwWaitResult = WaitForSingleObject(
			ev,		// event handle
			INFINITE	// indefinite wait
		);
		ResetEvent(evok);
		if (dwWaitResult != WAIT_OBJECT_0)
		{
			SetEvent(evok);
			continue;
		}
		ReadFile(pr_sum, &a, sizeof(a), &readed, NULL);
		if (readed != sizeof(a))
		{
			SetEvent(evok);
			continue;
		}
		ReadFile(pr_sum, &b, sizeof(b), &readed, NULL);
		if (readed != sizeof(b))
		{
			SetEvent(evok);
			continue;
		}
		a = a + b;
		WriteFile(pw_sum, &a, sizeof(a), &readed, NULL);
		SetEvent(evok);
	}
	return 0;
}

DWORD WINAPI t_sub(_In_ LPVOID LpParam)
{
	UNREFERENCED_PARAMETER(LpParam);
	HANDLE ev = OpenEvent(EVENT_ALL_ACCESS, FALSE, TEXT("sub"));
	HANDLE evok = OpenEvent(EVENT_ALL_ACCESS, FALSE, TEXT("calculated"));
	double a, b;
	DWORD readed;
	while (ev != NULL)
	{
		readed = 0;
		DWORD dwWaitResult = WaitForSingleObject(
			ev,		// event handle
			INFINITE	// indefinite wait
		);
		ResetEvent(evok);
		if (dwWaitResult != WAIT_OBJECT_0)
		{
			SetEvent(evok);
			continue;
		}
		ReadFile(pr_sub, &a, sizeof(a), &readed, NULL);
		if (readed != sizeof(a))
		{
			SetEvent(evok);
			continue;
		}
		ReadFile(pr_sub, &b, sizeof(b), &readed, NULL);
		if (readed != sizeof(b))
		{
			SetEvent(evok);
			continue;
		}
		a = a - b;
		WriteFile(pw_sub, &a, sizeof(a), &readed, NULL);
		SetEvent(evok);
	}
	return 0;
}

DWORD WINAPI t_mul(_In_ LPVOID LpParam)
{
	UNREFERENCED_PARAMETER(LpParam);
	HANDLE ev = OpenEvent(EVENT_ALL_ACCESS, FALSE, TEXT("mul"));
	HANDLE evok = OpenEvent(EVENT_ALL_ACCESS, FALSE, TEXT("calculated"));
	double a, b;
	DWORD readed;
	while (ev != NULL)
	{
		readed = 0;
		DWORD dwWaitResult = WaitForSingleObject(
			ev,		// event handle
			INFINITE	// indefinite wait
		);
		ResetEvent(evok);
		if (dwWaitResult != WAIT_OBJECT_0)
		{
			SetEvent(evok);
			continue;
		}
		ReadFile(pr_mul, &a, sizeof(a), &readed, NULL);
		if (readed != sizeof(a))
		{
			SetEvent(evok);
			continue;
		}
		ReadFile(pr_mul, &b, sizeof(b), &readed, NULL);
		if (readed != sizeof(b))
		{
			SetEvent(evok);
			continue;
		}
		a = a * b;
		WriteFile(pw_mul, &a, sizeof(a), &readed, NULL);
		SetEvent(evok);
	}
	return 0;
}

DWORD WINAPI t_div(_In_ LPVOID LpParam)
{
	UNREFERENCED_PARAMETER(LpParam);
	HANDLE ev = OpenEvent(EVENT_ALL_ACCESS, FALSE, TEXT("div"));
	HANDLE evok = OpenEvent(EVENT_ALL_ACCESS, FALSE, TEXT("calculated"));
	double a, b;
	DWORD readed;
	while (ev != NULL)
	{
		readed = 0;
		DWORD dwWaitResult = WaitForSingleObject(
			ev,		// event handle
			INFINITE	// indefinite wait
		);
		ResetEvent(evok);
		if (dwWaitResult != WAIT_OBJECT_0)
		{
			SetEvent(evok);
			continue;
		}
		ReadFile(pr_div, &a, sizeof(a), &readed, NULL);
		if (readed != sizeof(a))
		{
			SetEvent(evok);
			continue;
		}
		ReadFile(pr_div, &b, sizeof(b), &readed, NULL);
		if (readed != sizeof(b))
		{
			SetEvent(evok);
			continue;
		}
		if (b != 0)
			a = a / b;
		else
			a = NAN;
		WriteFile(pw_div, &a, sizeof(a), &readed, NULL);
		SetEvent(evok);
	}
	return 0;
}

DWORD WINAPI t_sqr(_In_ LPVOID LpParam)
{
	UNREFERENCED_PARAMETER(LpParam);
	HANDLE ev = OpenEvent(EVENT_ALL_ACCESS, FALSE, TEXT("sqr"));
	HANDLE evok = OpenEvent(EVENT_ALL_ACCESS, FALSE, TEXT("calculated"));
	double a;
	DWORD readed;
	while (ev != NULL)
	{
		readed = 0;
		DWORD dwWaitResult = WaitForSingleObject(
			ev,		// event handle
			INFINITE	// indefinite wait
		);
		ResetEvent(evok);
		if (dwWaitResult != WAIT_OBJECT_0)
		{
			SetEvent(evok);
			continue;
		}
		ReadFile(pr_sqr, &a, sizeof(a), &readed, NULL);
		if (readed != sizeof(a))
		{
			SetEvent(evok);
			continue;
		}
		a = a * a;
		WriteFile(pw_sqr, &a, sizeof(a), &readed, NULL);
		SetEvent(evok);
	}
	return 0;
}

DWORD WINAPI t_sqrt(_In_ LPVOID LpParam)
{
	UNREFERENCED_PARAMETER(LpParam);
	HANDLE ev = OpenEvent(EVENT_ALL_ACCESS, FALSE, TEXT("sqrt"));
	HANDLE evok = OpenEvent(EVENT_ALL_ACCESS, FALSE, TEXT("calculated"));
	double a;
	DWORD readed;
	while (ev != NULL)
	{
		readed = 0;
		DWORD dwWaitResult = WaitForSingleObject(
			ev,		// event handle
			INFINITE	// indefinite wait
		);
		ResetEvent(evok);
		if (dwWaitResult != WAIT_OBJECT_0 )
		{
			SetEvent(evok);
			continue;
		}
		ReadFile(pr_sqrt, &a, sizeof(a), &readed, NULL);
		if (readed != sizeof(a) || a < 0)
		{
			SetEvent(evok);
			continue;
		}
		a = sqrt(a);
		WriteFile(pw_sqrt, &a, sizeof(a), &readed, NULL);
		SetEvent(evok);
	}
	return 0;
}

int main(int argc, char* argv[])
{
	BOOL IsOk = FALSE;
	// Create Events
	ev_sum	= CreateEvent(NULL, FALSE, TRUE, TEXT("sum"));
	ev_sub	= CreateEvent(NULL, FALSE, TRUE, TEXT("sub"));
	ev_mul	= CreateEvent(NULL, FALSE, TRUE, TEXT("mul"));
	ev_div	= CreateEvent(NULL, FALSE, TRUE, TEXT("div"));
	ev_sqr	= CreateEvent(NULL, FALSE, TRUE, TEXT("sqr"));
	ev_sqrt = CreateEvent(NULL, FALSE, TRUE, TEXT("sqrt"));
	ev_ready = CreateEvent(NULL, FALSE, TRUE, TEXT("calculated"));
	if (GetLastError() != 0)
	{
		printf("Error [Create Events]: %zu\r\n", GetLastError());
		return -1;
	}
	// Create Channels
	IsOk |= CreatePipe(&pr_sum, &pw_sum, NULL, 64);
	IsOk |= CreatePipe(&pr_sub, &pw_sub, NULL, 64);
	IsOk |= CreatePipe(&pr_mul, &pw_mul, NULL, 64);
	IsOk |= CreatePipe(&pr_div, &pw_div, NULL, 64);
	IsOk |= CreatePipe(&pr_sqr, &pw_sqr, NULL, 64);
	IsOk |= CreatePipe(&pr_sqrt, &pw_sqrt, NULL, 64);
	if (!IsOk)
	{
		printf("Error [Create Channels]: %zu\r\n", GetLastError());
		return -1;
	}
	WaitForMultipleObjects(sizeof(events)/sizeof(events[0]), events,TRUE,INFINITE);
	// Create Threads
	ht_sum = CreateThread(NULL, 0, t_sum, NULL, SYNCHRONIZE, &threadIds[0]);
	ht_sub = CreateThread(NULL, 0, t_sub, NULL, SYNCHRONIZE, &threadIds[1]);
	ht_mul = CreateThread(NULL, 0, t_mul, NULL, SYNCHRONIZE, &threadIds[2]);
	ht_div = CreateThread(NULL, 0, t_div, NULL, SYNCHRONIZE, &threadIds[3]);
	ht_sqr = CreateThread(NULL, 0, t_sqr, NULL, SYNCHRONIZE, &threadIds[4]);
	ht_sqrt = CreateThread(NULL, 0, t_sqrt, NULL, SYNCHRONIZE, &threadIds[5]);
	if (GetLastError() != 0)
	{
		printf("Error [Create Threads]: %zu\r\n", GetLastError());
		return -1;
	}
	// Process sq. eq-n
	setlocale(0, "rus");
 	printf("¬ведите коэффициенты дл€ выражени€\n");
	double A = 1, B = 2, C = 1, B2, ac, ac4, D, negB, sqrtD, a2, x1_2, x1, x2_2, x2, imm2 = 2, imm4 = 4, imm0=0;

	scanf_s("%lf%lf%lf", &A, &B, &C);
	DWORD temp;
	printf("дано квадратное уравнение:\n %fX^2+(%f)X+(%f) = 0\r\n", A,B,C);
	
	WriteFile(pw_sqr, &B, sizeof(double), &temp, NULL);
	SetEvent(ev_sqr);
	WaitForSingleObject(ev_ready, INFINITE);
	ReadFile(pr_sqr, &B2, sizeof(double), &temp, NULL);
	printf("B2: %f\n", B2);

	WriteFile(pw_mul, &A, sizeof(double), &temp, NULL);
	WriteFile(pw_mul, &C, sizeof(double), &temp, NULL);
	SetEvent(ev_mul);
	WaitForSingleObject(ev_ready, INFINITE);
	ReadFile(pr_mul, &ac, sizeof(double), &temp, NULL);
	printf("ac: %f\n", ac);

	WriteFile(pw_mul, &ac, sizeof(double), &temp, NULL);
	WriteFile(pw_mul, &imm4, sizeof(double), &temp, NULL);
	SetEvent(ev_mul);
	WaitForSingleObject(ev_ready, INFINITE);
	ReadFile(pr_mul, &ac4, sizeof(double), &temp, NULL);
	printf("4ac: %f\n", ac4);

	WriteFile(pw_sub, &B2, sizeof(double), &temp, NULL);
	WriteFile(pw_sub, &ac4, sizeof(double), &temp, NULL);
	SetEvent(ev_sub);
	WaitForSingleObject(ev_ready, INFINITE);
	ReadFile(pr_sub, &D, sizeof(double), &temp, NULL);
	printf("D: %f\n", D);
	
	if (D < 0)
	{
		sqrtD = NAN;
		x1_2 = NAN;
		x1 = NAN;
		x2_2 = NAN;
		x2 = NAN;
	}
	else 
	{
		WriteFile(pw_mul, &A, sizeof(double), &temp, NULL);
		WriteFile(pw_mul, &imm2, sizeof(double), &temp, NULL);
		SetEvent(ev_mul);
		WaitForSingleObject(ev_ready, INFINITE);
		ReadFile(pr_mul, &a2, sizeof(double), &temp, NULL);
		negB = -B;



		if (D == 0)
		{
			sqrtD = 0;
			x1_2 = negB;


			WriteFile(pw_div, &x1_2, sizeof(double), &temp, NULL);
			WriteFile(pw_div, &a2, sizeof(double), &temp, NULL);
			SetEvent(ev_div);
			WaitForSingleObject(ev_ready, INFINITE);
			ReadFile(pr_div, &x1, sizeof(double), &temp, NULL);

			x2_2 = x1_2;
			x2 = x1;
		}
		else
		{

			WriteFile(pw_sqrt, &D, sizeof(double), &temp, NULL);
			SetEvent(ev_sqrt);
			WaitForSingleObject(ev_ready, INFINITE);
			ReadFile(pr_sqrt, &sqrtD, sizeof(double), &temp, NULL);



			WriteFile(pw_sub, &negB, sizeof(double), &temp, NULL);
			WriteFile(pw_sub, &sqrtD, sizeof(double), &temp, NULL);
			SetEvent(ev_sub);
			WaitForSingleObject(ev_ready, INFINITE);
			ReadFile(pr_sub, &x1_2, sizeof(double), &temp, NULL);

			WriteFile(pw_div, &x1_2, sizeof(double), &temp, NULL);
			WriteFile(pw_div, &a2, sizeof(double), &temp, NULL);
			SetEvent(ev_div);
			WaitForSingleObject(ev_ready, INFINITE);
			ReadFile(pr_div, &x1, sizeof(double), &temp, NULL);



			WriteFile(pw_sum, &negB, sizeof(double), &temp, NULL);
			WriteFile(pw_sum, &sqrtD, sizeof(double), &temp, NULL);
			SetEvent(ev_sum);
			WaitForSingleObject(ev_ready, INFINITE);
			ReadFile(pr_sum, &x2_2, sizeof(double), &temp, NULL);

			WriteFile(pw_div, &x2_2, sizeof(double), &temp, NULL);
			WriteFile(pw_div, &a2, sizeof(double), &temp, NULL);
			SetEvent(ev_div);
			WaitForSingleObject(ev_ready, INFINITE);
			ReadFile(pr_div, &x2, sizeof(double), &temp, NULL);		
		}

	}

	printf("X1 = %f/%f = %f\n", x1_2, a2, x1);
	printf("X2 = %f/%f = %f\n", x2_2, a2, x2);
	// Free objects
	ZeroMemory(&pipes, sizeof(pipes));
	TerminateThread(ht_sum, 0);
	TerminateThread(ht_sub, 0);
	TerminateThread(ht_mul, 0);
	TerminateThread(ht_div, 0);
	TerminateThread(ht_sqr, 0);
	TerminateThread(ht_sqrt, 0);
	return 0;
}