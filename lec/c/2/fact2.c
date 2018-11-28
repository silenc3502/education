#include <stdio.h>

int fact(int n)
{
	int first = 1;

	if(n < 1)
		return 1;

	while(n > 0)
		first *= n--;

	return first;
}

int main(void)
{
	int res;
	res = fact(5);
	printf("res = %d\n", res);

	return 0;
}
