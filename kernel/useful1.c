#include <stdio.h>

int main(void)
{
	int i = 0;

	printf("filename: %s\n", __FILE__);
	printf("current line: %d\n", __LINE__);
	printf("current function: %s\n", __FUNCTION__);
	printf("compile date: %s\n", __DATE__);
	printf("compile time: %s\n", __TIME__);
		
	return 0;
}
