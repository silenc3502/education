#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd;
	off_t new_pos;
	char buf[32] = "test test test";

	fd = open("reading.txt", O_RDWR);

	new_pos = lseek(fd, (off_t)-10, SEEK_END);

	printf("new_pos = %ld\n", new_pos);

	//write(fd, buf, sizeof(buf));

	close(fd);

	return 0;
}
