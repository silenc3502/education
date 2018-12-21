#include <stdio.h>

#define RESOLUTION      1 << 16
#define MINUS_VOLT      -5
#define PLUS_VOLT       5

float get_slice(void)
{
	return (float)(PLUS_VOLT - MINUS_VOLT) / (1 << 16);
}

float adc(int bit, float slice)
{
	return (float)(MINUS_VOLT) + bit * slice;
}

int main(void)
{
	float slice, volt;
	int bit = 12677;

	slice = get_slice();
	printf("slice = %f\n", slice);

	volt = adc(bit, slice);
	printf("volt = %f\n", volt);

	return 0;
}
