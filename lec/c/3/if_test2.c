#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int init_val(void)
{
	// 1 ~ 9
	// 실제 난수 생성
	return rand() % 9 + 1;
}

void check_num(int num)
{
	if(num == 0)
	{
		printf("num 은 0 이다\n");
	}
	// else 는 조건이 거짓인 경우에 들어갔음
	// else if 는 위의 조건이 거짓인 경우
	// 별도의 추가 조건을 걸어주기 위해 사용함
	else if(num % 2)
	{
		printf("num 은 홀수\n");
	}
	else
	{
		printf("num 은 짝수\n");
	}
}

int main(void)
{
	int num;

	// 임의의 난수(랜덤 넘버)를 생성하기 위한 초기 설정
	srand(time(NULL));

	num = init_val();
	printf("num = %d\n", num);
	check_num(num);

	return 0;
}
















