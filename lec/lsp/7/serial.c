#include "serial.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/poll.h>
#include <termios.h>
#include <fcntl.h>

struct pollfd poll_events;

char *dev0 = "/dev/ttyUSB0";

void recv_data(int fd)
{
	char rx_buf[32] = {0};

	while(poll((struct pollfd *)&poll_events, 1, 1000) > 0)
	{
		if(poll_events.revents & POLLIN)
		{
			usleep(5000);
			read(fd, rx_buf, sizeof(rx_buf));
			printf("%s", rx_buf);
		}
	}
}

int serial_config(char* dev)
{
	int    fd;
	//char tmp[1024] = {0};
	struct termios    newtio;

	fd = open( dev, O_RDWR | O_NOCTTY | O_NONBLOCK );        // 디바이스를 open 한다.

	if ( 0 > fd)
	{
		printf("%s open error\n", dev);
		exit(-1);
	}

	memset( &newtio, 0, sizeof(newtio) );
	newtio.c_cflag       = B9600 | CS8 | CLOCAL | CREAD;
	newtio.c_oflag       = 0;
	newtio.c_lflag       = 0;
	newtio.c_cc[VTIME]   = 0;
	newtio.c_cc[VMIN]    = 1;

	tcflush  (fd, TCIFLUSH );
	tcsetattr(fd, TCSANOW, &newtio );
	fcntl(fd, F_SETFL, FNDELAY);

	poll_events.fd        = fd;
	poll_events.events    = POLLIN | POLLERR;   // 수신된 자료가 있는지, 에러가 있는지
	poll_events.revents   = 0;

	printf("start\n");
	//write(fd, "T=1\r\n", 5);

	//printf("msg = \n");

	//while(read(fd, tmp, 1) > 0)
	//	printf("%s", tmp);

	printf("Ready to start parsing!\n");

	return fd;
}

inline void send_data(int fd, char *buf, int len, int utime)
{
	write(fd, buf, len);
	usleep(utime);
}

inline void close_dev(int fd)
{
	close(fd);
}
