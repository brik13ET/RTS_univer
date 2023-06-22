#include <Windows.h>
#include <stdio.h>
#include <stdint.h>
#include <locale.h>
#include <intrin.h>

#define matr_at(M,i,j) M[j*100 + i]
//2 Вариант BFDGJ  

void gist(uint64_t time_max_of_b, uint64_t time_min_of_b, uint64_t* time_of_b)
{
	uint64_t bufff = (time_max_of_b - time_min_of_b) / 10;
	for (int i = 0; i < 9; i++)
	{
		printf("%02.7e\t", time_min_of_b * i);
		for (int j = 0; j < 100; j++)
		{
			if (
				(time_min_of_b + bufff * i) < time_of_b[j] && time_of_b[j] < (time_min_of_b + bufff * (i + 1))
			)
				putchar('#');
		}
		putchar('\n');

	}
	putchar('\n');
	putchar('\n');
}

int main()
{
	setlocale(LC_ALL, "Russian");

	//заполнение матриц 
	int* matr1	= (int*)malloc(100 * 100 * sizeof(int));
	int* matr2	= (int*)malloc(100 * 100 * sizeof(int));
	int* res	= (int*)malloc(100 * 100 * sizeof(int));
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
		{
			matr_at(matr1, i, j) = rand();
			matr_at(matr2, i, j) = rand();
		}


	//заполнение массива случайными числами
	int* mass = (int*)malloc(1000 * sizeof(int));
	for (int i = 0; i < 1000; i++)
		mass[i] = rand();
	int buff = 0;

	int len = 100;
	uint64_t* time_start_of_f	= (uint64_t*)malloc(len * sizeof(uint64_t));
	uint64_t* time_start_of_d	= (uint64_t*)malloc(len * sizeof(uint64_t));
	uint64_t* time_start_of_g	= (uint64_t*)malloc(len * sizeof(uint64_t));
	uint64_t* time_start_of_fdg	= (uint64_t*)malloc(len * sizeof(uint64_t));
	uint64_t* time_end_of_f 	= (uint64_t*)malloc(len * sizeof(uint64_t));
	uint64_t* time_end_of_d 	= (uint64_t*)malloc(len * sizeof(uint64_t));
	uint64_t* time_end_of_g 	= (uint64_t*)malloc(len * sizeof(uint64_t));
	uint64_t* time_end_of_fdg	= (uint64_t*)malloc(len * sizeof(uint64_t));
	uint64_t* time_of_f 		= (uint64_t*)malloc(len * sizeof(uint64_t));
	uint64_t* time_of_d 		= (uint64_t*)malloc(len * sizeof(uint64_t));
	uint64_t* time_of_g 		= (uint64_t*)malloc(len * sizeof(uint64_t));
	uint64_t* time_of_fdg		= (uint64_t*)malloc(len * sizeof(uint64_t));
	uint64_t* time_of_f2		= (uint64_t*)malloc(len * sizeof(uint64_t));
	uint64_t* time_of_d2		= (uint64_t*)malloc(len * sizeof(uint64_t));
	uint64_t* time_of_g2		= (uint64_t*)malloc(len * sizeof(uint64_t));
	uint64_t* time_of_fdg2		= (uint64_t*)malloc(len * sizeof(uint64_t));

	printf("Инициализация успешна\n");

	//Измерение времени выполнения разложения на сомножители методом "brute force"
	for (int u = 0; u < len; u++)
	{
		time_start_of_f[u] = __rdtsc();
		int value = 909091;//1336337;614657
		for (int i = 2; i <= value; i++)
			if (value % i == 0)
				value = value / i;
		time_end_of_f[u] = __rdtsc();
		time_of_f[u] = (time_end_of_f[u] - time_start_of_f[u]);
		time_of_f2[u] = time_of_f[u] * time_of_f[u];
	}


	printf("Разложение окончено\n");

	//измерение времени выполнения сортировки пузырьком
	for (int i = 0; i < len; i++) {
		time_start_of_d[i] = __rdtsc();

		for (int i = 0; i < 1000 - 1; i++)
			for (int j = 0; j < 1000; j++)
				if (mass[i] < mass[j])
				{
					buff = mass[i];
					mass[i] = mass[j];
					mass[j] = buff;
				}

		time_end_of_d[i] = __rdtsc();
		time_of_d[i] = (time_end_of_d[i] - time_start_of_d[i]);
		time_of_d2[i] = time_of_d[i] * time_of_d[i];
	}

	printf("Сортировка окончена\n");
	//измерение времени выполнения умножения матриц
	for (int u = 0; u < len; u++)
	{
		time_start_of_g[u] = __rdtsc();

		for (int i = 0; i < 100; i++)
			for (int j = 0; j < 100; j++)
			{
				matr_at(res,i,j) = 0;
				for (int k = 0; k < 100; k++)
					matr_at(res, i, j) += matr_at(matr1,i,k) * matr_at(matr2,k,j);
			}

		time_end_of_g[u] = __rdtsc();
		time_of_g[u] = (time_end_of_g[u] - time_start_of_g[u]);
		time_of_g2[u] = time_of_g[u] * time_of_g[u];
	}

	printf("матричное умножение окончено\n");
	//измерение времени исполнения всех алгоритмов
	for (int k = 0; k < len; k++) 
	{
		float r = (float)rand() / (float)RAND_MAX;

		time_start_of_fdg[k] = __rdtsc();
		time_end_of_fdg[k] = time_start_of_fdg[k];
		time_end_of_fdg[k] += time_of_g[k];
		if (r < 0.5)
			time_end_of_fdg[k] += time_of_f[k];
		else
			time_end_of_fdg[k] += time_of_d[k];

		time_of_fdg[k] = (time_end_of_fdg[k] - time_start_of_fdg[k])*2;
		time_of_fdg2[k] = time_of_fdg[k] * time_of_fdg[k];
	}

	printf("общий прогон окончен\n");

	//поиск мах, мin и среднее, времени по формулам
	double time_max_of_f	= (double)time_of_f[0];
	double time_max_of_d	= (double)time_of_d[0];
	double time_max_of_g	= (double)time_of_g[0];
	double time_max_of_fdg	= (double)time_of_fdg[0];
	double time_min_of_f	= (double)time_of_f[0];
	double time_min_of_d	= (double)time_of_d[0];
	double time_min_of_g	= (double)time_of_g[0];
	double time_min_of_fdg	= (double)time_of_fdg[0];
	double time_mf			= 0;
	double time_md			= 0;
	double time_mg			= 0;
	double time_mfdg		= 0;
	double time_mfdg_formula= 0;
	double time_mf2			= 0;
	double time_md2			= 0;
	double time_mg2			= 0;
	double time_mfdg2		= 0;
	double time_d_f			= 0;
	double time_d_d			= 0;
	double time_d_g			= 0;
	double time_d_fdg		= 0;
	double time_d_fdg_formula= 0;
	for (int i = 0; i < len; i++)
	{
		if (time_of_f[i]	> time_max_of_f)	time_max_of_f	= time_of_f[i];
		if (time_of_f[i]	< time_min_of_f)	time_min_of_f	= time_of_f[i];
		if (time_of_d[i]	> time_max_of_d)	time_max_of_d	= time_of_d[i];
		if (time_of_d[i]	< time_min_of_d)	time_min_of_d	= time_of_d[i];
		if (time_of_g[i]	> time_max_of_g)	time_max_of_g	= time_of_g[i];
		if (time_of_g[i]	< time_min_of_g)	time_min_of_g	= time_of_g[i];
		if (time_of_fdg[i]	> time_max_of_fdg)	time_max_of_fdg	= time_of_fdg[i];
		if (time_of_fdg[i]	< time_min_of_fdg)	time_min_of_fdg	= time_of_fdg[i];
		time_mf		+= time_of_f[i];
		time_md		+= time_of_d[i];
		time_mg		+= time_of_g[i];
		time_mfdg	+= time_of_fdg[i];
		time_mf2	+= time_of_f2[i];
		time_md2	+= time_of_d2[i];
		time_mg2	+= time_of_g2[i];
		time_mfdg2	+= time_of_fdg2[i];
	}
	time_mf		/= len;
	time_md		/= len;
	time_mg		/= len;
	time_mfdg	/= len;

	time_mf2	/= len;
	time_md2	/= len;
	time_mg2	/= len;
	time_mfdg2	/= len;

	time_d_f	= time_mf2		- time_mf	* time_mf;
	time_d_d	= time_md2		- time_md	* time_md;
	time_d_g	= time_mg2		- time_mg	* time_mg;
	time_d_fdg	= time_mfdg2	- time_mfdg	* time_mfdg;

	time_mfdg_formula	= time_mf + (time_md + time_mg)/2;
	time_d_fdg_formula	= time_d_f + time_d_d + time_d_g + time_d_fdg;

	for (int i = 0; i < len - 1; i++)
		for (int j = 0; j < len; j++)
		{
			if (time_of_f[i] < time_of_f[j])
			{
				buff = time_of_f[i];
				time_of_f[i] = time_of_f[j];
				time_of_f[j] = buff;
			}
			if (time_of_d[i] < time_of_d[j])
			{
				buff = time_of_d[i];
				time_of_d[i] = time_of_d[j];
				time_of_d[j] = buff;
			}
			if (time_of_g[i] < time_of_g[j])
			{
				buff = time_of_g[i];
				time_of_g[i] = time_of_g[j];
				time_of_g[j] = buff;
			}
			if (time_of_fdg[i] < time_of_fdg[j])
			{
				buff = time_of_fdg[i];
				time_of_fdg[i] = time_of_fdg[j];
				time_of_fdg[j] = buff;
			}
		}

	printf(	"Алгоритм разложения на множители:\n"
			"Матожидание: %lf\n"
			"Дисперсия: %lf\n"
			"Max: %lf\n"
			"Min: %lf\n"
			"\n"
			"\n",
		time_mf / 3000000000,
		time_d_f / 3000000000,
		time_max_of_f / 3000000000,
		time_min_of_f / 3000000000

	);

	gist(time_max_of_f, time_min_of_f, time_of_f);

	printf(	"Алгоритм сортировки пузырьком:\n"
			"Матожидание: %lf\n"
			"Дисперсия: %lf\n"
			"Max: %lf\n"
			"Min: %lf\n"
			"\n"
			"\n",
		time_md / 3000000000,
		time_d_d / 3000000000,
		time_max_of_d / 3000000000,
		time_min_of_d / 3000000000
	);

	gist(time_max_of_d, time_min_of_d, time_of_d);

	printf(	"Алгоритм умножения матриц:\n"
			"Матожидание: %lf\n"
			"Дисперсия: %lf\n"
			"Max: %lf\n"
			"Min: %lf\n"
			"\n"
			"\n",
		time_mg / 3000000000,
		time_d_g / 3000000000,
		time_max_of_g / 3000000000,
		time_min_of_g / 3000000000

	);

	gist(time_max_of_g, time_min_of_g, time_of_g);

	printf(	"Алгоритм целиком:\n"
			"Матожидание: %lf\n"
			"Дисперсия: %lf\n"
			"Max: %lf\n"
			"Min: %lf\n"
			"\n"
			"\n",
		time_mfdg / 3000000000,
		time_d_fdg / 3000000000,
		time_max_of_fdg / 3000000000,
		time_min_of_fdg / 3000000000

	);

	gist(time_max_of_fdg, time_min_of_fdg, time_of_fdg);

	printf(	"Расчетные данные для всего алгоритма:\n"
			"Матожидание: %lf\n"
			"Дисперсия: %lf\n"
			"\n"
			"\n",
		time_mfdg_formula / 3000000000,
		time_d_fdg_formula / 3000000000

	);

	return 0;
}