#include <stdio.h>

// void (*)(void)
void test(void)
{
	printf("test\n");
}

// int (*)(void)
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

// ???? pof_test ????
// {
//     return test_test;
// }

// int (*)(void) test_test(void (*p)(void))
// int (*)(void) (*)(void (*)(void)) 리턴 타입
// void (*)(void) 인자
// int (*)(void) (*)(void (*)(void))
//     pof_test(void (*p)(void))
// int (*)(void) (* pof_test(void (*p)(void)))(void (*)(void))
// int (* (* pof_test(void (*p)(void)))(void (*)(void)))(void)
int (* (* pof_test(void (*p)(void)))(void (*)(void)))(void)
{
	printf("pof_test\n");
	p();
	return test_test;
}

int main(void)
{
	int res = pof_test(test)(test)();
	printf("res = %d\n", res);

	return 0;
}







