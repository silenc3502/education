#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void)
{
	int fd;

	fd = open("test.txt", O_CREAT);
	printf("fd = %d\n", fd);

	return 0;
}
