#include <stdio.h>

// one line comment
/* multi
   line
   comment */

#if 0
write here everything
#endif

#if __SPECIAL__
int A(int num)
{
	return num << 1;
/*
	return num * 2;
*/
}
#endif

int main(void)
{
	int res;
	int num1 = 3;

	res = A(num1);
	printf("res = %d\n", res);

	return 0;
}
