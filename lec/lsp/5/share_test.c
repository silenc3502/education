#include <stdio.h>

int main(void)
{
	int *p = 0x7ffef5c6e4d4;
	//int *p = 0x7ffc37b63834;

	printf("&a = %p\n", *p);

	return 0;
}
