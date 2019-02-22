#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd;
	off_t new_pos;

	fd = open("reading.txt", O_RDONLY);

	new_pos = lseek(fd, (off_t)0, SEEK_END);

	printf("new_pos = %ld\n", new_pos);

	close(fd);

	return 0;
}
