/* 배열 100 개를 선언한다.
   그리고 난수를 돌려서
   임의의 값을 배열에 채워넣는다.
   이 때 채워넣은 개수가
   동일하지 않게 난수를 생성하도록 한다.
   난수 생성 범위는 1 ~ 9 로 하도록 한다.

   ex) 1, 1, 1, 2, 2, 2, 2 - OK
       1, 1, 1, 2, 2, 2    - X
       1, 1, 2, 2, 3, 3, 3 - X
       1, 2, 2, 3, 3, 3, 3 - OK

   이후에 생성한 값들을 출력하도록 한다.
   그리고 이들 중에 가장 빈도수가
   가장 높은 3 개의 숫자를
   출력하도록 프로그래밍 하시오. */
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

void init_rand_num(int arr[])
{
	int i;

	for(i = 0; i < 100; i++)
	{
		arr[i] = rand() % 9 + 1;
	}
}

void make_freq_table(int ft[], int fn[])
{
	int i;

	for(i = 0; i < 100; i++)
	{
		ft[fn[i]]++;
	}
}

void print_arr(int arr[], int len)
{
	int i, flag = 1;

	for(i = 1; i < len + 1; i++)
	{
		printf("%3d", arr[i - 1]);

		if(!(i % 10))
		{
			printf("\n");
		}
	}
}

bool check_dup(int freq_tab[], int len)
{
	int i, j;

	for(i = 1; i < len; i++)
	{
		for(j = len - 1; j > 0; j--)
		{
			if(freq_tab[i] == freq_tab[j])
			{
				memset(freq_tab, 0x0, 40);
				return true;
			}
		}
	}

	return false;
}

int main(void)
{
	int freq_num[100] = {0};
	int freq_tab[11] = {0};
	int max_tab[4] = {0};

	srand(time(NULL));

	init_rand_num(freq_num);
	printf("Print Random Number\n");
	print_arr(freq_num, 100);

	printf("Print Frequency Table\n");
	make_freq_table(freq_tab, freq_num);
	print_arr(freq_tab, 10);

#if 1
	if(check_dup(freq_tab, sizeof(freq_tab)/sizeof(int)))
	{
		printf("Dup!\n");
	}
	else
	{
		printf("No Dup!\n");
	}
#endif

	return 0;
}
