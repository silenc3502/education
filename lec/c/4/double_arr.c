#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void init_arr(int arr[][2])
{
	int i, j;

	srand(time(NULL));

	for(i = 0; i < 3; i++)
		for(j = 0; j < 2; j++)
			arr[i][j] = rand() % 5 + 1;
}

void print_arr(int arr[3][2])
{
	int i, j;

	for(i = 0; i < 3; i++)
		for(j = 0; j < 2; j++)
			printf("arr[%d][%d] = %d\n", i, j, arr[i][j]);
}

void print_addr(int arr[][2])
{
	int i, j;

	printf("arr addr = 0x%x\n", arr);

	for(i = 0; i < 3; i++)
		for(j = 0; j < 2; j++)
			printf("arr[%d][%d] addr = 0x%x\n", i, j, &arr[i][j]);
}

int main(void)
{
	int arr[3][2] = {0};

	init_arr(arr);
	print_arr(arr);
	print_addr(arr);
	
	return 0;
}








