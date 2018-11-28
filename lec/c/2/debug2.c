#include <stdio.h>

int my_func(int n1, int n2, int n3, int n4)
{
	return n1 + n2 + n3 + n4;
}

int main(void)
{
	int res;
	int n1 = 1, n2 = 2, n3 = 3, n4 = 4;
	res = my_func(n1, n2, n3, n4);
	printf("res = %d\n", res);

	return 0;
}
