#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

void my_system(char *cmd)
{
	int pid;
	int status;

	char *argv[] = {"bash", "-c", cmd, 0};
	char *envp[] = {0};

	if((pid = fork()) > 0)
		wait(&status);
	else if(!pid)
		execve("/bin/bash", argv, envp);
}

int main(void)
{
	my_system("date");
	printf("after date kkk\n");

	return 0;
}






