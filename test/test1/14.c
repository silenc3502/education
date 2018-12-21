#include <stdio.h>

void make_series(long long int *arr, int fin)
{
	int i;

	for(i = 2; i < fin; i++)
		arr[i] = arr[i - 2] + arr[i - 1];
}

void print_arr(long long int *arr)
{
	int i, cnt = 1;

	for(i = 0; arr[i]; i++)
	{
		printf("%12lld ", arr[i]);

		if(!(cnt++ % 5))
			printf("\n");
	}

	printf("\n");
}

long long int get_sum(long long int *arr,
						long long int *os,
						long long int *es)
{
	int i;

	for(i = 0; arr[i]; i++)
	{
		if(arr[i] % 2)
			*os += arr[i];
		else
			*es += arr[i];
	}
}

int main(void)
{
	long long int arr[128] = {1, 1, 2};
	long long int odd_sum = 0, even_sum = 0;

	make_series(arr, 57);
	print_arr(arr);

	get_sum(arr, &odd_sum, &even_sum);
	printf("odd_sum  = %16lld\n", odd_sum);
	printf("even_sum = %16lld\n", even_sum);

	printf("res = %lld\n", odd_sum - even_sum);

	return 0;
}
