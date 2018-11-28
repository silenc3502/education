#include <stdio.h>

int main(void)
{
	int num = 3;

	int *p = &num;
	int **pp = &p;

	printf("**pp = %d\n", **pp);

	return 0;
}
