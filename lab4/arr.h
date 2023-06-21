#ifndef ARR_H
#define ARR_H
#include <stdint.h>
#include <stdbool.h>

#define Array_At(A,i) A.data[i]
#define Array_Size(A) A.size

typedef struct
{
	int32_t* data;
	size_t size;
}arr;

arr 	Array_New	 (size_t cnt);
void	Array_Fill	 (arr A);
void	Array_Sort	 (arr A);
void	Array_Delete (arr A);

#endif