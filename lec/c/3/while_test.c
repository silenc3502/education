#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// 랜덤 넘버 생성
int rand_init(void)
{
	srand(time(NULL));
	return rand() % 10 + 1;
}

void while_test(int num)
{
	int cnt = 0;

	/* while 의 괄호 안에는 조건을 적는다.
	   조건은 값이 있으면 참
	   값이 0 이면 거짓에 해당한다.
	   즉 num 의 숫자만큼 cnt++ 을 반복하게됨

	   추가적으로 ++ 은 + 1 과 같은 의미이며
	   -- 는 - 1 과 같은 의미다.
	   즉 현재 cnt 가 0 인 상태에서
	   ++ 하면cnt 는 1 이 되고
	   그 이후에 ++ 하면 cnt 는 2 가 된다. */
	while(num--)
	{
		cnt++;
	}

	printf("cnt = %d\n", cnt);
}

void find_even(int num)
{
	int cnt = 1;

	while(cnt <= num)
	{
		if(!(cnt % 2))
			printf("%4d", cnt);

		cnt++;
	}

	printf("\n");
}

int main(void)
{
	int num = rand_init();
	printf("num = %d\n", num);

	while_test(num);
	find_even(num);

	return 0;
}





