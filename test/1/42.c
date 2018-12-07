#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **init_double_arr(int imax, int jmax)
{
	int i, j, k, tmp;
	static int **arr = NULL;

	arr = (int **)malloc(sizeof(int *) * imax);

	for(i = 0; i < imax; i++)
		arr[i] = (int *)malloc(sizeof(int) * jmax);

	for(i = 0; i < imax; i++)
	{
		for(j = 0; j < jmax; j++)
		{
redo:
			tmp = rand() % 9;

			for(k = j - 1; k >= 0; k--)
				if(tmp == arr[i][k])
					goto redo;

			arr[i][j] = tmp;
		}
	}

	return arr;
}

void init_idx(int *imax, int *jmax)
{
	*imax = rand() % 3 + 2;
	*jmax = rand() % 3 + 3;

	printf("imax = %d\n", *imax);
	printf("jmax = %d\n", *jmax);
}

void print_double_arr(int **arr, int imax, int jmax)
{
	int i, j;

	for(i = 0; i < imax; i++)
	{
		for(j = 0; j < jmax; j++)
			printf("%3d ", arr[i][j]);

		printf("\n");
	}
}

int *init_arr(int max)
{
	static int *arr = NULL;

	arr = (int *)malloc(sizeof(int) * max);

	return arr;
}

void transform_format(int *res, int **arr, int imax, int jmax)
{
	int i, j;

	for(i = 0; i < imax; i++)
		for(j = 0; j < jmax; j++)
			res[i] += arr[i][j] * pow(10, (jmax - 1) - j);
}

void print_arr(int *arr, int max)
{
	int i;

	for(i = 0; i < max; i++)
		printf("%6d\n", arr[i]);
}

void sort_ascend(int *arr, int len)
{
	int i, j, key;

	for(i = 1; i < len; i++)
	{
		key = arr[i];

		for(j = i - 1; arr[j] > key; j--)
			arr[j + 1] = arr[j];

		arr[j + 1] = key;
	}
}

void inverse_transform(int *arr, int **res, int imax, int jmax)
{
	int i, j;

	for(i = 0; i < imax; i++)
		for(j = 0; j < jmax; j++)
			res[i][j] = (int)(arr[i] / pow(10, (jmax - 1) - j)) % 10;
}

int main(void)
{
	int imax, jmax;
	int **arr = NULL;
	int *res;

	srand(time(NULL));

	init_idx(&imax, &jmax);
	arr = init_double_arr(imax, jmax);
	print_double_arr(arr, imax, jmax);

	printf("After Transform\n");
	res = init_arr(imax);
	transform_format(res, arr, imax, jmax);
	print_arr(res, imax);

	printf("After Sorting\n");
	sort_ascend(res, imax);
	print_arr(res, imax);

	printf("Inverse Transform\n");
	inverse_transform(res, arr, imax, jmax);
	print_double_arr(arr, imax, jmax);

	return 0;
}
