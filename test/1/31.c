#include <stdio.h>
#include <math.h>

#define RESOLUTION      1 << 24
#define MINUS_VOLT      -12
#define PLUS_VOLT       12
#define CUR_VOLT        9.7f

float get_slice(void)
{
	return (float)(PLUS_VOLT - MINUS_VOLT) / (1 << 24);
}

float dac(int digital, float slice)
{
	return CUR_VOLT / slice;
}

int main(void)
{
	float slice;
	float digital;

	slice = get_slice();
	printf("slice = %f\n", slice);

	digital = dac(digital, slice);
	printf("digital = %f\n", digital);
	printf("round(digital) = %f\n", round(digital));
	printf("round(digital) = 0x%x\n", (int)round(digital));

	return 0;
}
