#include <stdio.h>

int cnt;

int fib(int n)
{
	cnt++;
	if(n <= 2)
		return 1;

	return fib(n-1) + fib(n-2);
}

int main(void)
{
	int res;
	res = fib(6);
	printf("res = %d\n", res);

	printf("몇 번 계산되는가 ? %d\n", cnt);

	return 0;
}
