#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Usage: exe del_file\n");
		exit(-1);
	}

	unlink(argv[1]);

	return 0;
}
