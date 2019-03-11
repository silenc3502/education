#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(void)
{
	pid_t pid;

	pid = fork();

	if(pid > 0)
		printf("P\n");
	else if(!pid)
		printf("C\n");
	else
	{
		perror("fork()");
		exit(-1);
	}

	return 0;
}
