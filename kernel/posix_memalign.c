#include <emmintrin.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

typedef struct timeval	tv;

// Usage: ./a.out 64000000
double get_runtime(tv start, tv end)
{
	end.tv_usec = end.tv_usec - start.tv_usec;
	end.tv_sec = end.tv_sec - start.tv_sec;
	end.tv_usec += end.tv_sec * 1000000;

#if 1
	printf("runtime = %lf sec\n", end.tv_usec / 1000000.0);
#endif

	return end.tv_usec / 1000000.0;
}

void normal(float *a, int N)
{
	int i;
	for(i = 0; i < N; ++i)
		a[i] = sqrt(a[i]);
}

void normal2(char *a, const char *b, int N)
{
	int i;
	for(i = 0; i < N; ++i)
		a[i] += b[i];
}

void sse(float *a, int N)
{
	int i;

	// We assume N % 4 == 0.
	int nb_iters = N / 4;
	__m128* ptr = (__m128*)a;

	for(i = 0; i < nb_iters; ++i, ++ptr, a += 4)
		_mm_store_ps(a, _mm_sqrt_ps(*ptr));
}

void sse2(char *a, const char *b, int N)
{
	int i;
	int nb_iters = N / 16;

	__m128i* l = (__m128i*)a;
	__m128i* r = (__m128i*)b;

	for(i = 0; i < nb_iters; ++i, ++l, ++r)
		_mm_store_si128(l, _mm_add_epi8(*l, *r));
}

int main(int argc, char** argv)
{
	int i;
	float *a;
	char *one;
	char *two;
	tv start, end;
	int N = atoi(argv[1]);

	if(argc != 2)
		return 1;

	posix_memalign((void**)&a, 16,  N * sizeof(float));
	posix_memalign((void**)&one, 16,  N * sizeof(char));
	posix_memalign((void**)&two, 16,  N * sizeof(char));

	for(i = 0; i < N; ++i)
		a[i] = 3141592.65358;

	printf("normal:\t\t");
	{
		gettimeofday(&start, NULL);
		normal(a, N);
		gettimeofday(&end, NULL);
	}

	get_runtime(start, end);

	for(i = 0; i < N; ++i)
		a[i] = 3141592.65358;

	printf("sse:\t\t");
	{
		gettimeofday(&start, NULL);
		sse(a, N);
		gettimeofday(&end, NULL);
	}

	get_runtime(start, end);

	for(i = 0; i < N; ++i)
	{
		one[i] = 33;
		two[i] = 77;
	}

	printf("normal2:\t");
	{
		gettimeofday(&start, NULL);
		normal2(one, two, N);
		gettimeofday(&end, NULL);
	}

	get_runtime(start, end);

	for(i = 0; i < N; ++i)
	{
		one[i] = 33;
		two[i] = 77;
	}

	printf("sse2:\t\t");
	{
		gettimeofday(&start, NULL);
		sse2(one, two, N);
		gettimeofday(&end, NULL);
	}

	get_runtime(start, end);

	return 0;
}
