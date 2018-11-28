#include <stdio.h>

void init_arr(int (*arr)[2])
{
	int i, j, cnt = 1;

	for(i = 0; i < 3; i++)
		for(j = 0; j < 2; j++)
			arr[i][j] = cnt++;
}

void print_arr(int (*arr)[2])
{
	int i, j;

	for(i = 0; i < 3; i++)
		for(j = 0; j < 2; j++)
			printf("arr[%d][%d] = %d\n", i, j, arr[i][j]);
}

void init_pnt_arr(int **pnt_arr, int (*arr)[2])
{
	int i;

	for(i = 0; i < 3; i++)
		pnt_arr[i] = arr[i];
}

/* int (*)[3] p */
void test_arr_pnt(int (*p)[3])
{
	int i, j;

	for(i = 0; i < 2; i++)
		for(j = 0; j < 3; j++)
			printf("p[%d][%d] = %d\n", i, j, p[i][j]);
}

void test_arr_func(int (*p)[2])
{
	printf("**p = %d\n", **p);
	printf("*(*p + 1) = %d\n", *(*p + 1));
	printf("*(*p + 3) = %d\n", *(*p + 3));
	printf("**(p + 1) = %d\n", **(p + 1));
	printf("**(p + 2) = %d\n", **(p + 2));
}

int main(void)
{
	int i;
	int arr[3][2] = {0};		/* int (*)[2] arr */
	/* ([][])([][])([][])
	   뒤쪽의 대괄호는 가장 작은 단위가 몇 개 있는지
	   그 앞쪽의 대괄호는 그 작은 단위의 묶음이 몇 개 있는지를 나타냄 */
	int *pnt_arr[3] = {0};		/* 포인터 배열 */
								/* 데이터 타입: ((int *)[ ]) */
	int (*p)[3] = NULL;			/* 배열 포인터 */
								/* 데이터 타입: (int (*)[3]) */

	init_arr(arr);
	print_arr(arr);

	init_pnt_arr(pnt_arr, arr);

	for(i = 0; i < 3; i++)
		printf("*pnt_arr[%d] = %d\n", i, *pnt_arr[i]);

	p = arr;
	printf("p[0] = %d\n", *p[0]);
	printf("p[1] = %d\n", *p[1]);

	test_arr_pnt(p);

	test_arr_func(arr);

	return 0;
}

















