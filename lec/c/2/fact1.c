#include <stdio.h>

int fact(int n)
{
	if(n < 1)
		return 1;

	return n * fact(n - 1);
}

int main(void)
{
	int res;
	res = fact(5);
	printf("res = %d\n", res);

	return 0;
}
