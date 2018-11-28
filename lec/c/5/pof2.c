#include <stdio.h>

// void (*)(void)
void test(void)
{
	printf("test\n");
}

// int (*p)[3] vs int *p[3]
// int[3](*) p vs (int *)[3] p
// int[3]* p vs (int *)[3] p

// void (*)(void) test_test(void)
void (* test_test(void))(void)
{
	printf("test_test\n");
	return test;
}

int main(void)
{
	test_test()();

	return 0;
}
