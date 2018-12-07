#include <stdio.h>
#include <string.h>

typedef struct __test test;
struct __test
{
	int num1;
	float num2;
};

void exchg_data(test *t1, test *t2)
{
	test tmp;

	memmove(&tmp, t1, sizeof(test));
	memmove(t1, t2, sizeof(test));
	memmove(t2, &tmp, sizeof(test));
}

void print_struct(test t1, test t2)
{
	printf("t1.num1 = %d, t1.num2 = %f\n", t1.num1, t1.num2);
	printf("t2.num1 = %d, t2.num2 = %f\n", t2.num1, t2.num2);
}

int main(void)
{
	test t1 = {3, 7.7};
	test t2 = {7, 3.3};

	print_struct(t1, t2);
	exchg_data(&t1, &t2);
	print_struct(t1, t2);

	return 0;
}
