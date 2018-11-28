#include <stdio.h>

int fib(int n)
{
	int tmp, first = 1, second = 1;

	if(n <= 2)
		return 1;

	n -= 2;

	while(n--)
	{
		tmp = first + second;
		first = second;
		second = tmp;
	}

	return tmp;
}

int main(void)
{
	int res;
	res = fib(5);
	printf("res = %d\n", res);

	return 0;
}
