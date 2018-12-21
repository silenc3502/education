// gcc -D__DEBUG__ 60.c 혹은 gcc 60.c
#include <stdio.h>

void test(void)
{
#ifdef __DEBUG__
	printf("Debug!\n");
#else
	printf("Release!\n");
#endif
}

int main(void)
{
	test();
	return 0;
}
