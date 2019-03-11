#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(void)
{
	int i;
	pid_t pid;

	pid = fork();

	if(pid > 0)
	{
		for(;;)
		{
			for(i = 0; i < 33; i++)
				printf("P");
			printf("\n");
		}
	}
	else if(!pid)
	{
		for(;;)
		{
			for(i = 0; i < 77; i++)
				printf("C");
			printf("\n");
		}
	}
	else
	{
		perror("fork()");
		exit(-1);
	}

	return 0;
}
