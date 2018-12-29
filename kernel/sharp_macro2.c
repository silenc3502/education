#include <stdio.h>

#define macro_test(value)		test_##value

int main(void)
{
	int data = 0;
	int test_data = 77;

	printf("%d\n", macro_test(data));

	return 0;
}
