#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#define	TEST1		777777777
#define TEST2		2222222222

typedef struct timeval tv;

double get_runtime(tv start, tv end)
{
	end.tv_usec = end.tv_usec - start.tv_usec;
	end.tv_sec = end.tv_sec - start.tv_sec;
	end.tv_usec += end.tv_sec * 1000000;

	printf("runtime = %lf sec\n", end.tv_usec / 1000000.0);

	return end.tv_usec / 1000000.0;
}

int main(void)
{
	unsigned int i, cnt = 0;
	tv start, end;

	gettimeofday(&start, NULL);

	for(i = 0; i < TEST2; i++)
		cnt++;

	gettimeofday(&end, NULL);

	get_runtime(start, end);

	return 0;
}
