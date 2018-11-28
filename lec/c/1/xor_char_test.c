#include <stdio.h>

int main(void)
{
	char ch1 = 'A';
	char ch2 = 'a';

	printf("ch1 ^ 0x20 = %c\n", ch1 ^ 0x20);
	printf("ch2 ^ 0x20 = %c\n", ch2 ^ 0x20);

	return 0;
}
