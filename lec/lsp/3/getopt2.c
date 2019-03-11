#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#define A_OPT			1
#define L_OPT			2
#define R_OPT			4

int main(int argc, char **argv)
{
	DIR *dp;
	int i = 1, cmd;
	int opt_flag = 0;
	struct dirent *p;

	while((cmd = getopt(argc, argv, "alR")) > 0)
	{
		switch(cmd)
		{
			case 'a':
				opt_flag |= A_OPT;
				break;
			case 'l':
				opt_flag |= L_OPT;
				break;
			case 'R':
				opt_flag |= R_OPT;
				break;
			default:
				break;
		}
	}

	printf("opt_flag = %d\n", opt_flag);

	dp = opendir(".");

	while(p = readdir(dp))
	{
		if(!(opt_flag & A_OPT))
			if(p->d_name[0] == '.')
				continue;

		printf("%-12s ", p->d_name);

		if(!(i++ % 5))
			printf("\n");
	}

	printf("\n");
	closedir(dp);

	return 0;
}












