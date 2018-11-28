#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int init_num(void)
{
	return rand() % 33 + 1;
}

bool check_num(int num, int c1, int c2)
{
	// ! 는 관계 연산자 not
	// && 는 관계 연산자 and
	// 주의: 비트 연산자 아님
	if(!(num % c1) && !(num % c2))
		return true;

	return false;
}

int main(void)
{
	int num;

	srand(time(NULL));

	num = init_num();

	printf("num = %d\n", num);

	if(check_num(num, 2, 3))
	{
		printf("이것은 2 와 3 의 배수\n");
	}
	else
	{
		printf("이것은 2 와 3 의 배수가 아님\n");
	}

	return 0;
}
