#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int a = 10;

	printf("&a = %p\n", &a);

	sleep(1000);

	return 0;
}
