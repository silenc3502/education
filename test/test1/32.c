#include <stdbool.h>
#include <stdio.h>
#include <math.h>

double rad_2_deg(double rad)
{
	return rad * 180.0 / M_PI;
}

double deg_2_rad(double deg)
{
	return deg * M_PI / 180.0;
}

double fact(double val)
{
	double first = 1;

	while(val > 0)
		first = first * val--;

	return first;
}

double taylor_sin(double rad)
{
	double res = 0;

	res = rad - pow(rad, 3.0) / fact(3) + pow(rad, 5.0) / fact(5)
			- pow(rad, 7.0) / fact(7) + pow(rad, 9.0) / fact(9);

	return res;
}

bool check_sin(void)
{
	double math_sin = sin(M_PI/4.0);
	double my_sin = taylor_sin(M_PI/4.0);

	printf("math_sin = %lf, pi/4 = %lf degree\n",
			math_sin, rad_2_deg(M_PI/4.0));
	printf("my_sin = %lf\n", my_sin);

	if((int)math_sin * 1000000 == (int)my_sin * 1000000)
		return true;
	else
		return false;
}

int main(void)
{
	bool res = check_sin();

	if(res)
		printf("It's similar\n");
	else
		printf("It's not similar\n");

	return 0;
}
