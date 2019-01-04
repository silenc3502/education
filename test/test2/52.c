#include <math.h>
#include <stdio.h>

#define ARR_SHIFT		(10)
#define SAMPLE_NUM		((1) << (ARR_SHIFT))
#define ARR_SIZE		((SAMPLE_NUM) + (1))
#define ARR_DIVIDE		((SAMPLE_NUM) - (1))



#if 0
void gen_rect_waveform(float *arr, float *samp_x)
{
	int i;

	for(i = 0; i < SAMPLE_NUM; i++)
		arr[i] = 0.5;
}
#else
void gen_rect_waveform(double *arr, double *samp_x, double range)
{
	int i, j;

	//for(j = 0; j < ARR_SIZE; j++)
	for(j = 0; j < SAMPLE_NUM; j++)
	{
		for(i = 1; i < 101; i++)
			arr[j] += ((1 - cos((i) * M_PI)) * sin((i) * samp_x[j])) / ((i) * M_PI);
			//arr[j] += ((1 - cos((i) * M_PI)) * sin((i) * samp_x[j])) / ((i) * M_PI);

		arr[j] += 0.5;
	}
}
#endif

double calc_slice(double start, double end)
{
	//return (end - start) / SAMPLE_NUM;
	return (end - start) / ARR_DIVIDE;
}

void calc_sample_x(double *arr, double range)
{
	int i;

	//for(i = 0; i < ARR_SIZE; i++)
	for(i = 0; i < SAMPLE_NUM; i++)
		arr[i] = -M_PI + range * i;
}

void print_arr(double *arr)
{
	int i;

	//for(i = 0; i < ARR_SIZE; i++)
	for(i = 0; i < SAMPLE_NUM; i++)
		printf("sample x[%d] = %.12lf\n", i, arr[i]);
}

int main(void)
{
	double sam_range;
	double data_arr[ARR_SIZE] = {0};
	double sample_x[ARR_SIZE] = {0};
	//double arr[65537] = {0};

	sam_range = calc_slice(-M_PI, M_PI);
	//printf("slice(sample range) = %.16lf\n", sam_range);

	calc_sample_x(sample_x, sam_range);
	//print_arr(sample_x);
	//printf("M_PI =     %.12lf\n", M_PI);

	gen_rect_waveform(data_arr, sample_x, sam_range);
	print_arr(data_arr);

	return 0;
}
