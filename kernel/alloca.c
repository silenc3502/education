#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>

void init_arr(int *arr)
{
	int i;

	for(i = 0; i < 5; i++)
		arr[i] = rand() % 7;
}

void print_arr(int *arr)
{
	int i;

	for(i = 0; i < 5; i++)
		printf("arr[%d] = %d\n", i, arr[i]);
}

int main(void)
{
	int *arr = alloca(5 * sizeof(*arr));

	srand(time(NULL));

	init_arr(arr);
	print_arr(arr);

	return 0;
}
