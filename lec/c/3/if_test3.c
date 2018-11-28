#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int init_val(void)
{
	return rand() % 9 + 1;
}

void check_num(int num)
{
	if(num == 0)
	{
		printf("num 은 0 이다\n");
	}
	else
	{
		if(num % 2)
		{
			printf("num 은 홀수\n");
		}
		else
		{
			printf("num 은 짝수\n");
		}
	}
}

int main(void)
{
	int num;

	srand(time(NULL));

	num = init_val();
	printf("num = %d\n", num);
	check_num(num);

	return 0;
}
















