#include <stdio.h>
#include <math.h>

int calc_piece(float interval, float dx)
{
	return interval / dx;
}

float calc_int_3x_2_7x(float start, float end)
{
	int i, int_s, int_e;
	float sum = 0.0f;
	float temp = 0.0f;
	const float exp = 2.0;
	const float dx = 0.0001f;

	float dy = pow(dx, exp);

	printf("dx = %.10f\n", dx);
	printf("dy = %.10f\n", dy);

	int_s = 0.0f;
	int_e = calc_piece(end - start, dx);

	printf("int_e = %d\n", int_e);

	for (i = int_s; i < int_e; i++)
	{
		temp += dx;
		dy = 3 * pow(temp + start, exp) + 7 * (temp + start);
		sum += dx * dy;
	}

	printf("sum = %f\n", sum);

	return sum;
}

int main(void)
{
	float res;
	res = calc_int_3x_2_7x(1.0f, 2.0f);
	printf("res = %f\n", res);

	return 0;
}
