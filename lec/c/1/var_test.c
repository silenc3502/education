#include <stdio.h>

int main(void)
{
	int num1 = 3;
	float num2 = 7.0f;
	double num3 = 3.3;

	printf("num2 x num3 = %.1lf\n", num2 * num3);
	printf("num2 / num3 = %lf\n", num2 / num3);
	printf("num1 %% 7 = %d\n", num1 % 7);
	printf("num1 %% 2 = %d\n", num1 % 2);

	return 0;
}
