#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int main(void)
{
	DIR *dp;
	int i = 0;
	struct dirent *p;

	dp = opendir(".");

	while(p = readdir(dp))
	{
		if(p->d_name[0] == '.')
			continue;

		printf("%-12s ", p->d_name);

		//if((i + 1) % 5 == 0)
		if(!((i + 1) % 5))
			printf("\n");

		i++;
	}

	printf("\n");
	closedir(dp);

	return 0;
}
