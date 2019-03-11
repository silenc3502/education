#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
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

typedef struct _arg
{
	int start;
	int end;
} arg;

typedef struct timeval tv;

double get_runtime(tv start, tv end)
{
	end.tv_usec = end.tv_usec - start.tv_usec;
	end.tv_sec = end.tv_sec - start.tv_sec;
	end.tv_usec += end.tv_sec * 1000000;

	printf("runtime = %.9lf sec\n", end.tv_usec / 1000000.0);

	return end.tv_usec / 1000000.0;
}

void *t1(void *x)
{
	int i;
	arg set = *(arg *)x;

	for(i = set.start; i < set.end; i++)
		arr[i] = arr[i - 1] + init[i];

	//pthread_exit((void *)&i);
	pthread_exit((void *)arr[i - 1]);
	//return (void *)&arr[i - 1];
}

void *t2(void *x)
{
	int i, sum = 0;
	arg set = *(arg *)x;

	for(i = set.start; i < set.end; i++)
		sum += init[i];

	pthread_exit((void *)sum);
	//return (void *)ret;
}

int main(void)
{
	pthread_t thread[3] = {0};
	unsigned int i, cnt = 0;
	tv start, end;
	int ret[3] = {0}; 
	int fin = 0;
	arg one = {1, PTEST / 2};
	arg two = {PTEST / 2, PTEST};

	srand(time(NULL));

	for(i = 0; i < PTEST; i++)
		init[i] = rand() % 10 + 1;

	gettimeofday(&start, NULL);

	for(i = 1; i < PTEST; i++)
		arr[i] = arr[i - 1] + init[i];

	gettimeofday(&end, NULL);

	printf("arr[%d] = %d\n", PTEST - 1, arr[PTEST - 1]);

	get_runtime(start, end);

	gettimeofday(&start, NULL);

	pthread_create(&thread[0], NULL, t1, (void *)&one);
	pthread_create(&thread[1], NULL, t2, (void *)&two);

	pthread_join(thread[0], (void **)&ret[0]);
	pthread_join(thread[1], (void **)&ret[1]);

	gettimeofday(&end, NULL);

	printf("ret[0] = %d\n", ret[0]);
	printf("ret[1] = %d\n", ret[1]);
	printf("arr[%d] = %d\n", PTEST - 1, ret[0] + ret[1]);

	get_runtime(start, end);

	return 0;
}
