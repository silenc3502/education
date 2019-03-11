#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int status;
	pid_t pid;

	if((pid = vfork()) > 0)
	{
		wait(&status);
		printf("ls -al test Success\n");
	}
	else if(!pid)
	{
		execlp("ls", "ls", "-a", "-l", 0);
	}

	return 0;
}
