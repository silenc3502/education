#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void)
{
	int status;
	int pid;

	char *argv[] = {"./ls_l", "ls_l2.c", 0};
	char *envp[] = {0};

	if((pid = fork()) > 0)
	{
		wait(&status);
		printf("Child was finished\n");
	}
	else if(!pid)
	{
		execve("./ls_l", argv, envp);
	}

	return 0;
}
