#include <stdio.h>

char only_once_oper(char c)
{
	return c ^ 0x20;
}

int main(void)
{
	char c1 = 'X', c2 = 'p';

	printf("c1 = %c\n", only_once_oper(c1));
	printf("c2 = %c\n", only_once_oper(c2));

	return 0;
}
