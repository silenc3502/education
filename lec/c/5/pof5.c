#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void init_arr(int (*arr)[2])
{
	int i, j;

	srand(time(NULL));

	for(i = 0; i < 2; i++)
		for(j = 0; j < 2; j++)
		{
			arr[i][j] = rand() % 9 + 1;
			printf("arr[%d][%d] = %d\n", i, j, arr[i][j]);
		}
}

#if 0
// 이것은 지역 변수를 return 하는 것이므로 동작하지 않음
int (* cant_ret_arr(void))[2]
{
	int arr[2][2] = {0};

	init_arr(arr);

	return arr;
}
#endif

void test(void)
{
	printf("test\n");
}

// int (*)[2] arr_ret(void)
int (* arr_ret(void))[2]
{
	// static 은 선언된 함수 내에서만 전역 변수 처럼 동작
	static int arr[2][2] = {0};

	init_arr(arr);

	return arr;
}

// int (*)[2] arr_ret(void) arr_pof(void (*p)(void))
// int (*)[2] (*)(void) arr_pof(void (*p)(void))
// int (*)[2] (* arr_pof(void (*p)(void)))(void)
// int (* (* arr_pof(void (*p)(void)))(void))[2]
int (* (* arr_pof(void (*p)(void)))(void))[2]
{
	printf("arr_pof\n");
	p();
	return arr_ret;
}

int main(void)
{
	int i, j;
	int (*p)[2];

	p = arr_ret();
	printf("p[0][0] = %d\n", p[0][0]);

#if 0
	// int (* cant_ret_arr(void))[2]
	p = cant_ret_arr();
	printf("p[0][0] = %d\n", p[0][0]);

	// printf("arr = 0x%x\n", arr);
#endif

	p = arr_pof(test)();

	for(i = 0; i < 2; i++)
		for(j = 0; j < 2; j++)
			printf("p[%d][%d] = %d\n", i, j, p[i][j]);

	return 0;
}









