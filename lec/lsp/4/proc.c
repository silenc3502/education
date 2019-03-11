#include <unistd.h>
#include <stdio.h>

int main(void)
{
	printf("before\n");

	fork();

	printf("after\n");
	
	return 0;
}
