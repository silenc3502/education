#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int init_rand(void)
{
	return rand() % (1 << 29) + 1;
}

int ordering(int x)
{
	return x & ~((1 << 27) - 1);
}

int main(void)
{
	int x;

	srand(time(NULL));

	x = init_rand();
	printf("0x%x\n", ordering(x));

	return 0;
}
