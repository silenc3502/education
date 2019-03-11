#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

#define	TEST1			777777777
#define TEST2			2222222222

//#define PTEST			250000000
#define PTEST			125000000
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

int check_remain(int num)
{
	return PTEST % num;
}

void config_arg_idx(arg *idx, char *argv)
{
	int i, max = atoi(argv);
	int remain_num;
	int cnt = 0;

	remain_num = check_remain(max);

	printf("remain_num = %d\n", remain_num);

	idx[0].start = 1;

	if(remain_num--)
	{
		cnt++;
		idx[0].end = (int)((PTEST / max) + cnt);
	}
	else
		idx[0].end = (int)(PTEST / max);

#if 0
	printf("idx[0].start = %d\n", idx[0].start);
	printf("idx[0].end = %d\n", idx[0].end);
#endif

	for(i = 1; i < max; i++)
	{
		idx[i].start = idx[i - 1].end;
		if(remain_num-- > 0)
		{
			cnt++;
			idx[i].end = (int)((PTEST / max) * (i + 1) + cnt);
		}
		else if(i == max - 1)
			idx[i].end = PTEST;
		else
			idx[i].end = (int)((PTEST / max) * (i + 1));

#if 0
		printf("idx[%d].start = %d\n", i, idx[i].start);
		printf("idx[%d].end = %d\n", i, idx[i].end);
#endif
	}
}

void print_idx(arg *idx, char *argv)
{
	int i, num = atoi(argv);

	for(i = 0; i < num; i++)
	{
		printf("idx[%d].start = %d\n", i, idx[i].start);
		printf("idx[%d].end = %d\n", i, idx[i].end);
	}
}

int main(int argc, char **argv)
{
	pthread_t thread[16] = {0};
	unsigned int i, cnt = 0;
	tv start, end;
	int ret[16] = {0}; 
	int fin = 0;

#if 0
	arg one = {1, PTEST / 2};
	arg two = {PTEST / 2, PTEST};
#endif

	arg idx[9];
	int num;

	if(argc != 2)
	{
		printf("Usage: exe num_of_thread\n");
		exit(-1);
	}

	num = atoi(argv[1]);

	srand(time(NULL));

	for(i = 0; i < PTEST; i++)
		init[i] = rand() % 10 + 1;

	config_arg_idx(idx, argv[1]);
	print_idx(idx, argv[1]);

	gettimeofday(&start, NULL);

	for(i = 1; i < PTEST; i++)
		arr[i] = arr[i - 1] + init[i];

	gettimeofday(&end, NULL);

	printf("arr[%d] = %d\n", PTEST - 1, arr[PTEST - 1]);

	get_runtime(start, end);

#if 1
	gettimeofday(&start, NULL);

	pthread_create(&thread[0], NULL, t1, (void *)&idx[0]);

	for(i = 1; i < num; i++)
		pthread_create(&thread[i], NULL, t2, (void *)&idx[i]);
		//pthread_create(&thread[1], NULL, t2, (void *)&two);

	for(i = 0; i < num; i++)
		pthread_join(thread[i], (void **)&ret[i]);
		//pthread_join(thread[1], (void **)&ret[1]);

	gettimeofday(&end, NULL);

	for(i = 0; i < num; i++)
	{
		printf("ret[%d] = %d\n", i, ret[i]);
		//printf("ret[1] = %d\n", ret[1]);

		fin += ret[i];
	}

	printf("arr[%d] = %d\n", PTEST - 1, fin);

	get_runtime(start, end);
#endif

	return 0;
}
