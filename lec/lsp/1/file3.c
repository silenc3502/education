#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void)
{
	int fd;
	int nw;
	char text[64] = "Hello Linux System Programming!";

	fd = open("test.txt", O_CREAT | O_WRONLY, 0644);
	printf("fd = %d\n", fd);

	nw = write(fd, text, strlen(text) + 1);
	printf("nw = %d\n", nw);

	close(fd);

	return 0;
}
