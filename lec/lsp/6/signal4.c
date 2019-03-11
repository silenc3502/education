#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void my_sig(int signo)
{
	printf("You must insert coin\n");
	exit(0);
}

int main(void)
{
	char buf[1024] = {0};
	int ret;

	signal(SIGALRM, my_sig);

	for(;;)
	{
		alarm(10);

		if((ret = read(0, buf, sizeof(buf))) > 0)
		{
			buf[ret - 1] = '\0';
			printf("Insert %s\n", buf);
		}

		printf("After\n");
		alarm(0);
	}

	return 0;
}




