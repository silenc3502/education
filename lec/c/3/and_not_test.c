#include <stdio.h>

int and_not(int num)
{
	// 여기서 비트 필터링을 수행
	// 1 << 4 = 16 - 1 = 15
	// 10000 - 00001 = 01111
	// ~01111 = 11110000
	// n & 11110000
	// 하위 4 비트는 무조건 걸러짐
	// 즉 16 의 배수로 정렬함을 의미함
	return num & ~((1 << 4) - 1);
}

int main(void)
{
	int res = and_not(33);
	printf("res = %d\n", res);
	res = and_not(40);
	printf("res = %d\n", res);
	res = and_not(65);
	printf("res = %d\n", res);
	res = and_not(63);
	printf("res = %d\n", res);
	res = and_not(21);
	printf("res = %d\n", res);

	return 0;
}
