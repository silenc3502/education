#include <stdio.h>
#include <pthread.h>

void *task1(void *x)
{
	for(;;)
		printf("Thread A Complete\n");
}

void *task2(void *x)
{
	for(;;)
		printf("Thread B Complete\n");
}

int main(void)
{
	pthread_t A, B;

	pthread_create(&A, NULL, task1, NULL);
	pthread_create(&B, NULL, task2, NULL);

	pthread_join(A, NULL);
	pthread_join(B, NULL);

	return 0;
}
