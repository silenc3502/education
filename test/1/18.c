#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void set_rand_mem(int *mem)
{
	int i;

	for(i = 0; i < 100; i++)
		mem[i] = rand() % 4096 + 1;
}

void print_mem(int *mem)
{
	int i;

	for(i = 0; i < 100; i++)
		printf("mem[%d] = %d\n", i, mem[i]);
}

int main(void)
{
	int mem[100] = {0};

	srand(time(NULL));
	set_rand_mem(mem);

	print_mem(mem);

	return 0;
}
