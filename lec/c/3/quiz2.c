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

#if 0
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
#endif

bool check_dup(int max_tab[], int ft[], int len)
{
	int i, j;

	for(i = 0; i < len; i++)
	{
		for(j = i + 1; j < len; j++)
		{
			if(max_tab[i] == max_tab[j])
			{
				memset(ft, 0x0, 40);
				return true;
			}
		}
	}

	return false;
}

void make_max_tab(int max_tab[], int freq_tab[])
{
	int i, j, key, len = 10;

	// 삽입 정렬 알고리즘
	// 데이터의 개수가 적을때 빠름
	// 데이터의 개수가 정해져 있을 경우엔
	// Quick Sort 도 빠름
	for(i = len - 1; i > 0; i--)
	{
		key = freq_tab[i - 1];

		for(j = i; freq_tab[j] > key; j++)
			freq_tab[j - 1] = freq_tab[j];

		freq_tab[j - 1] = key;
	}

	printf("max freq_tab: ");

	for(i = 0; i < 11; i++)
		printf("%3d", freq_tab[i]);

	printf("\n");

	for(i = 0; i < 3; i++)
		max_tab[i] = freq_tab[i];
}

int main(void)
{
	int freq_num[100] = {0};
	int freq_tab[11] = {0};
	int max_tab[4] = {0};

	srand(time(NULL));

	while(check_dup(max_tab, freq_tab, 3))
	{
		init_rand_num(freq_num);
		printf("Print Random Number\n");
		print_arr(freq_num, 100);

		printf("Print Frequency Table\n");
		make_freq_table(freq_tab, freq_num);
		print_arr(freq_tab, 10);

		printf("Print Max Number\n");
		make_max_tab(max_tab, freq_tab);
	}

	printf("Successful to avoid redundancy!\n");
	print_arr(max_tab, 3);
	printf("\n");

	return 0;
}








