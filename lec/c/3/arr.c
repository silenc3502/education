#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int init_rand(void)
{
	int res;
	srand(time(NULL));
	res = rand() % 10 + 1;
	printf("res = %d\n", res);

	return res;
}

// int *arr
void init_arr(int arr[10], int num)
{
	int i;

	for(i = 0; i < num; i++)
		arr[i] = i;
}

void print_arr(int arr[10], int len)
{
	int i;

	for(i = 0; i < len; i++)
		printf("arr[%d] = %d\n", i, arr[i]);
}

int main(void)
{
	// int 형 배열을 10 개 선언 및 초기화
	// {0} 자동으로 전부 0 으로 초기화
	// int 는 데이터 타입이고
	// [] 대괄호 안은 배열의 개수
	// 데이터 타입과 대괄호 사이에는 이름이 온다.
	int arr[10] = {0};

	/* init_rand() 가 예로 3 을 가져왔다고 가정
	   그렇다면 init_arr(arr, 3) 과 같음
	   *** 배열의 이름은 주소다 ***
	   엄밀하게 배열의 이름은 시작주소인데
	   기계어에서 봤듯이
	   모든 개념은 주소 개념으로 보는게 좋음 */
	init_arr(arr, init_rand());
	print_arr(arr, sizeof(arr)/sizeof(int));
	
	return 0;
}








