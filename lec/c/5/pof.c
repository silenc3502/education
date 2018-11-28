#include <stdio.h>

// void (*)(void)
void test(void)
{
	printf("test\n");
}

int main(void)
{
	void (*p)(void) = test;
	p();

	return 0;
}
