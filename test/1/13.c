#include <stdio.h>

void make_series(int *arr, int fin)
{
	int i;

	for(i = 2; i < fin; i++)
		arr[i] = arr[i - 2] + arr[i - 1];
}

void print_arr(int *arr)
{
	int i, cnt = 1;

	for(i = 0; arr[i]; i++)
	{
		printf("%6d ", arr[i]);

		if(!(cnt++ % 5))
			printf("\n");
	}

	printf("\n");
}

int main(void)
{
	int arr[128] = {1, 3};

	make_series(arr, 23);
	print_arr(arr);

	return 0;
}
