#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **init_arr(int imax, int jmax)
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
}

void print_arr(int **arr, int imax, int jmax)
{
	int i, j;

	for(i = 0; i < imax; i++)
	{
		for(j = 0; j < jmax; j++)
			printf("%3d ", arr[i][j]);

		printf("\n");
	}
}

int main(void)
{
	int imax, jmax;
	int **arr = NULL;

	srand(time(NULL));

	init_idx(&imax, &jmax);
	arr = init_arr(imax, jmax);
	print_arr(arr, imax, jmax);

	return 0;
}
