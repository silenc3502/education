#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#define	TEST1			777777777
#define TEST2			2222222222

#define PTEST			250000000
//#define PTEST			125000000
//#define PTEST			62500000
//#define PTEST			31250000
//#define PTEST			8

int arr[PTEST] = {7, };
int init[PTEST];

typedef struct timeval tv;

double get_runtime(tv start, tv end)
{
	end.tv_usec = end.tv_usec - start.tv_usec;
	end.tv_sec = end.tv_sec - start.tv_sec;
	end.tv_usec += end.tv_sec * 1000000;

	printf("runtime = %.9lf sec\n", end.tv_usec / 1000000.0);

	return end.tv_usec / 1000000.0;
}

int main(void)
{
	unsigned int i, cnt = 0;
	tv start, end;

	srand(time(NULL));

	for(i = 0; i < PTEST; i++)
		init[i] = rand() % 10 + 1;

	gettimeofday(&start, NULL);

	for(i = 1; i < PTEST; i++)
		arr[i] = arr[i - 1] + init[i];

	gettimeofday(&end, NULL);

	printf("arr[%d] = %d\n", PTEST - 1, arr[PTEST - 1]);

	get_runtime(start, end);

	arr[PTEST - 1] = 0;

	gettimeofday(&start, NULL);

	for(i = 1; i < PTEST; i++)
		arr[PTEST - 1] += init[i];

	arr[PTEST - 1] += arr[0];

	gettimeofday(&end, NULL);

	printf("arr[%d] = %d\n", PTEST - 1, arr[PTEST - 1]);

	get_runtime(start, end);

	return 0;
}
