#include <stdlib.h>
#include <arr.h>

arr Array_New(size_t cnt)
{
	return (arr){ .data = (int32_t*)calloc(cnt,sizeof(int32_t)), .size = cnt };
	
}

void Array_Fill(arr A)
{
	for (size_t i = 0; i < Array_Size(A); i++)
		Array_At(A, i) = rand();
}

void Array_Sort(arr A)
{
	bool sorted = false;

	while (!sorted)
	{
		for (size_t i = 0; i < Array_Size(A); i++)
			if (Array_At(A, i) < Array_At(A, i + 1))
			{
				int32_t tmp = Array_At(A, i);
				Array_At(A, i) = Array_At(A, i + 1);
				Array_At(A, i + 1) = tmp;
			}

		for (size_t i = 0; i < Array_Size(A) - 1 && !sorted; i++)
			sorted = Array_At(A, i) >= Array_At(A, i + 1);
	}
}

void Array_Delete(arr A)
{
	free(A.data);
	A.data = 0;
	A.size = 0;
}

