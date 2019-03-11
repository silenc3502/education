#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void)
{
	int fd, ret;
	char buf[256] = {0};

	//mkfifo("myfifo", 0664);
	fd = open("myfifo", O_RDWR);

	fcntl(0, F_SETFL, O_NONBLOCK);
	fcntl(fd, F_SETFL, O_NONBLOCK);

	for(;;)
	{
		if((ret = read(0, buf, sizeof(buf))) > 0)
		{
			buf[ret - 1] = 0;
			printf("Keyboard In: [%s]\n", buf);
		}
	
		if((ret = read(fd, buf, sizeof(buf))) > 0)
		{
			buf[ret - 1] = 0;
			printf("Pipe In: [%s]\n", buf);
		}
	}

	return 0;
}
