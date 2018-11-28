#include <stdio.h>

// void (*)(void)
void test(void)
{
	printf("test\n");
}

int num_test(void)
{
	printf("num_test\n");
	return 7;
}

// int (*)(void) test_test(void (*p)(void))
int (* test_test(void (*p)(void)))(void)
{
	printf("test_test\n");
	p();
	return num_test;
}

int main(void)
{
	int res = test_test(test)();
	printf("res = %d\n", res);

	return 0;
}


