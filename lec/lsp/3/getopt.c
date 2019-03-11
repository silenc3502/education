#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int cmd;

	while((cmd = getopt(argc, argv, "alR")) > 0)
	{
		switch(cmd)
		{
			case 'a':
				printf("a option\n");
				break;
			case 'l':
				printf("l option\n");
				break;
			case 'R':
				printf("R option\n");
				break;
			default:
				printf("exe -a or l or R\n");
				break;
		}
	}

	return 0;
}
