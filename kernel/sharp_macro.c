#include <stdio.h>

#define	macro_test(num)			#num

int main(void)
{
	int str = 0;

	printf("%s\n", macro_test(str));

	return 0;
}
