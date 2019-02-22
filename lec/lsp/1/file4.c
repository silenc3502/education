#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void)
{
	int i = 0;
	int len;
	int fd;
	int nw;

	char text[64] = "Hello Linux System Programming!";
	len = strlen(text);
	printf("len = %d\n", len);

	fd = open("test.txt", O_CREAT | O_WRONLY, 0644);
	printf("fd = %d\n", fd);


	while(i < 32)
		write(fd, &text[i++], 1);

	close(fd);

	return 0;
}
