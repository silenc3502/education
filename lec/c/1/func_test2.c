#include <stdio.h>

float mult(int num1, float num2)
{
	return num1 * num2;
}

int main(void)
{
	float num1 = 3.3;
	float res;

	res = mult(2, num1);
	printf("res = %.1f\n", res);

	return 0;
}
