#include <stdio.h>
#include <math.h>

float ang2rad(int ang)
{
	return (float)ang * M_PI / 180.0f;
}

void tri_syn(int x, int y)
{
	float res_rad = ang2rad(x + y);
	float cos_75, cos_15, sin_75, sin_15;
	float cos_45, cos_30, sin_45, sin_30;
	printf("75 degree = %f radian\n", res_rad);

	cos_45 = cos(ang2rad(x));
	printf("cos(45) = %f\n", cos_45);

	cos_30 = cos(ang2rad(y));
	printf("cos(30) = %f\n", cos_30);

	sin_45 = sin(ang2rad(x));
	printf("sin(45) = %f\n", sin_45);

	sin_30 = sin(ang2rad(y));
	printf("sin(30) = %f\n", sin_30);

	cos_75 = cos_45 * cos_30 - sin_45 * sin_30;
	printf("cos(75) = %f\tmath_cos(75) = %f\n", cos_75, cos(ang2rad(x + y)));

	cos_15 = cos_45 * cos_30 + sin_45 * sin_30;
	printf("cos(15) = %f\tmath_cos(15) = %f\n", cos_15, cos(ang2rad(x - y)));

	sin_75 = cos_45 * sin_30 + sin_45 * cos_30;
	printf("sin(75) = %f\tmath_sin(75) = %f\n", sin_75, sin(ang2rad(x + y)));

	sin_15 = sin_45 * cos_30 - cos_45 * sin_30;
	printf("sin(15) = %f\tmath_sin(15) = %f\n", sin_15, sin(ang2rad(x - y)));
}

void tri_add_sub(int x, int y)
{
	float cos_45x30, sin_45x30, sin_45xcos_30, cos_45xsin_30;

	cos_45x30 = 0.5 * (cos(ang2rad(x + y)) + cos(ang2rad(x - y)));
	printf("cos(45) * cos(30) = %f\tmath_res = %f\n", cos_45x30, cos(ang2rad(x)) * cos(ang2rad(y)));

	sin_45x30 = 0.5 * (cos(ang2rad(x - y)) - cos(ang2rad(x + y)));
	printf("sin(45) * sin(30) = %f\tmath_res = %f\n", sin_45x30, sin(ang2rad(x)) * sin(ang2rad(y)));

	sin_45xcos_30 = 0.5 * (sin(ang2rad(x + y)) + sin(ang2rad(x - y)));
	printf("sin(45) * cos(30) = %f\tmath_res = %f\n", sin_45xcos_30, sin(ang2rad(x)) * cos(ang2rad(y)));

	cos_45xsin_30 = 0.5 * (sin(ang2rad(x + y)) - sin(ang2rad(x - y)));
	printf("cos(45) * sin(30) = %f\tmath_res = %f\n", cos_45xsin_30, cos(ang2rad(x)) * sin(ang2rad(y)));
}

int main(void)
{
	tri_syn(45, 30);
	tri_add_sub(45, 30);
	return 0;
}
