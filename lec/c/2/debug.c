#include <stdio.h>

int mult(int num)
{
	return num * 2;
}

int main(void)
{
	int res;
	int num1 = 3;
	res = mult(num1);
	printf("res = %d\n", res);
	printf("check (char *) = %lu\n", sizeof(char *));
	printf("check (int *) = %lu\n", sizeof(int *));
	printf("check (float *) = %lu\n", sizeof(float *));
	printf("check (double *) = %lu\n", sizeof(double *));
	return 0;
}
