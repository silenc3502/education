#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void term_status(int status)
{
	if(WIFEXITED(status))
		printf("(exit)status: 0x%x\n", WEXITSTATUS(status));
	else if(WTERMSIG(status))
		printf("(signal)status: 0x%x\n", status & 0x7f);
}

void my_sig(int signo)
{
	int status;

	printf("signo = %d\n", signo);

	//wait(&status);
	while(waitpid(-1, &status, WNOHANG) > 0)
		term_status(status);
}

void my_int(int signo)
{
	printf("signo = %d\n", signo);
	exit(-1);
}

int main(void)
{
	int i;
	pid_t pid;

	signal(SIGCHLD, my_sig);
	signal(SIGINT, my_int);

	if((pid = fork()) > 0)
	{
		for(i = 0; i < 10000; i++)
		{
			usleep(50000);
			printf("%d\n", i + 1);
		}
	}
	else if(!pid)
	{
		sleep(50);
		abort();
	}
	else
	{
		perror("fork() ");
		exit(-1);
	}

	return 0;
}




