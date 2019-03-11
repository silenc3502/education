#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	struct stat buf;
	char ch;

	if(argc != 2)
	{
		printf("Usage: exe filename or dirname\n");
		exit(-1);
	}

	stat(argv[1], &buf);

	if(S_ISDIR(buf.st_mode))
		ch = 'd';
	else if(S_ISREG(buf.st_mode))
		ch = '-';
	else if(S_ISFIFO(buf.st_mode))
		ch = 'p';
	else if(S_ISCHR(buf.st_mode))
		ch = 'c';
	else if(S_ISBLK(buf.st_mode))
		ch = 'b';

	printf("dir type = %c\n", ch);

	return 0;
}
