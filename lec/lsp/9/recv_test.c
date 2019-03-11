#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

extern char *dev0;
jmp_buf env;
int fd;

void call_exit(int signo)
{
	//close_dev(fd);
	longjmp(env, 1);
}

int main(void)
{
	int ret, nr;
	char buf[64] = "";
	int len;

//	fd = serial_config(dev0);
	signal(SIGINT, call_exit);

	if(!(ret = setjmp(env)))
	{
		for(;;)
		{
			nr = read(0, buf, sizeof(buf));
			buf[nr - 1] = 0;
			//printf("buf = %s\n", buf);

#if 0
			send_data(fd, buf, len, 50);
			recv_data(fd);
#endif
		}
	}

	return 0;
}
