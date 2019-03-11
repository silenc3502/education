#include <unistd.h>
#include <stdio.h>

int main(void)
{
	execlp("ls", "ls", "-a", "-l", 0);
	printf("ls -al test Success\n");

	return 0;
}
