#include <stdio.h>

#define FIX_CONST		20

typedef struct __test
{
	int num_int;
	float num_float;
	double num_double;
	char name[FIX_CONST];
} test;

int main(void)
{
	test t = {3, 7.7f, 3.3, "gogogo"};
	printf("t.num_int = %d\n", t.num_int);
	printf("t.num_float = %f\n", t.num_float);
	printf("t.num_double = %lf\n", t.num_double);
	printf("t.name = %s\n", t.name);

	return 0;
}




