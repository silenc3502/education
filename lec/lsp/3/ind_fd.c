#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	char buf[64] = {0};
	int fd[2] = {0};
	int i;

	for(i = 0; i < 2; i++)
	{
		fd[i] = open("test.txt", O_RDONLY);
		printf("fd[%d] = %d\n", i, fd[i]);
		read(fd[i], buf, 10);
		write(1, buf, 10);
	}

	return 0;
}
