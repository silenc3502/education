#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

extern char *dev0;
int fd;

typedef struct sockaddr_in		si;
typedef struct sockaddr *		sap;

#define BUF_SIZE				1024

void err_handler(char *msg)
{
	fputs(msg, stderr);
	fputs('\n', stderr);
	exit(1);
}

int main(int argc, char **argv)
{
	int i, str_len;
	int serv_sock, clnt_sock;

	char serial_buf[64] = "";
	char msg[BUF_SIZE];
	char write_buf[BUF_SIZE] = "success\n";

	si serv_addr;
	si clnt_addr;
	socklen_t clnt_addr_size;

	//char msg[] = "Hello Network Programming~~!!~!\n";

	if(argc != 2)
	{
		printf("Usage: %s <port>\n", argv[0]);
		exit(-1);
	}

	fd = serial_config(dev0);

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);

	if(serv_sock == -1)
		err_handler("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	if(bind(serv_sock, (sap)&serv_addr, sizeof(serv_addr)) == -1)
		err_handler("bind() error");

	if(listen(serv_sock, 10) == -1)
		err_handler("listen() error");

	clnt_addr_size = sizeof(clnt_addr);

	clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);

	if(clnt_sock == -1)
		err_handler("accept() error");

	while((str_len = read(clnt_sock, serial_buf, BUF_SIZE)) != 0)
	{
		send_data(fd, serial_buf, len, 50);
		write(clnt_sock, write_buf, sizeof(write_buf));
	}

	close(clnt_sock);
	close(serv_sock);

	return 0;
}









