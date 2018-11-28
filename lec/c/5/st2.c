#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FIX_CONST		20

typedef struct __test
{
	int num_int;
	float num_float;
	double num_double;
	char name[FIX_CONST];
} test;

test *init_struct(void)
{
	test *t = (test *)malloc(sizeof(test));

	t->num_int = 3;
	t->num_float = 3.3f;
	t->num_double = 7.7;
	strcpy(t->name, "test!!!");

	return t;
}

void print_struct(test **t)
{
	printf("num_int = %d\n", (*t)->num_int);
	printf("num_float = %f\n", (*t)->num_float);
	printf("num_double = %lf\n", (*t)->num_double);
	printf("name = %s\n", (*t)->name);
}

int main(void)
{
	test *t = NULL;

	t = init_struct();
	print_struct(&t);

	free(t);

	return 0;
}




