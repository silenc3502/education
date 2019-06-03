#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define NMAX		10000000

#if _DEBUG_
void chk_rand_max(void)
{
	printf("rand max(int) = %d\n", RAND_MAX);
	printf("rand min(int) = %d\n", -RAND_MAX - 1);
	printf("range = %u\n", 2 * (unsigned int)RAND_MAX + 1);
}
#endif

double *get_sample(int num, double mean, double std_dev)
{
	int i;
	double *values = (double *)calloc(num, sizeof(double));

	for(i = 0; i < num; i++)
	{
        double x, y, r;

        do
        {
            x = 2.0 * rand() / RAND_MAX - 1;
            y = 2.0 * rand() / RAND_MAX - 1;
   
            r = x*x + y*y;
        }
        while (r == 0.0 || r > 1.0);

        double d = sqrt(-2.0 * log(r) / r);
        double n1 = x * d;
   	    double result = n1*std_dev + mean;
		values[i] = result;
    }

	return values;
}

double *make_hist(double *sbuf, int num)
{
	int i;
	double *hbuf = NULL;
	// 85899346 * 50 = 4294967300
	// uint max      = 4294967295
	// 42949673 * 50 = 2147483650
	double width_range = 0.05;
	int range = 20;		// 1 / width_range
	int idx;

	hbuf = (double *)malloc(sizeof(double) * range);
	memset(hbuf, 0x0, sizeof(double) * range);

	printf("num of hbuf elements = %d\n", range);

	for(i = 0; i < num; i++)
	{
		idx = sbuf[i] / width_range;
		hbuf[idx]++;
	}

	return hbuf;
}

void print_hist(double *hbuf)
{
	int i;
	double width_range = 0.05;
	int hist_range = 20;	// 1 / width_range

	for(i = 0; i < hist_range; i++)
	{
		printf("hbuf[%d] = %lf\n", i, hbuf[i]);
	}
}

int main(void)
{
	double *sbuf = NULL;
	double *hist_buf = NULL;

	srand(time(NULL));

#if _DEBUG_
	chk_rand_max();
#endif

	if((sbuf = get_sample(NMAX, 0.5, 0.2)) != NULL)
	{
		hist_buf = make_hist(sbuf, NMAX);
		free(sbuf);
		sleep(5);
		print_hist(hist_buf);
		free(hist_buf);
	}
	
	return 0;
}
