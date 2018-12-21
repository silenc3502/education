#include <stdio.h>

void insert_sort_descend(int *arr, int len)
{
	int i, j, key;

	for(i = len - 1; i > 0; i--)
	{
		key = arr[i - 1];

		for(j = i; arr[j] > key; j++)
			arr[j - 1] = arr[j];

		arr[j - 1] = key;
	}

}

void print_arr(int *arr, int len)
{
	int i;

	printf("data = \n");

	for(i = 0; i < len; i++)
		printf("%3d ", arr[i]);

	printf("\n");
}

int main(void)
{
	int data[7] = {5, 2, 4, 6, 1, 3};

	insert_sort_descend(data, sizeof(data)/sizeof(int) - 1);
	print_arr(data, 6);

	return 0;
}
