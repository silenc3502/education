#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

void recursive_dir(char *dname)
{
	struct dirent *p;
	struct stat buf;
	DIR *dp;

	chdir(dname);
	dp = opendir(".");
	printf("%s:\n", dname);

	while(p = readdir(dp))
		printf("\t\t%s\n", p->d_name);

	rewinddir(dp);

	while(p = readdir(dp))
	{
		stat(p->d_name, &buf);

		if(S_ISDIR(buf.st_mode))
			if(strcmp(p->d_name, ".") && strcmp(p->d_name, ".."))
				recursive_dir(p->d_name);
	}

	chdir("..");
	closedir(dp);
}

int main(void)
{
	recursive_dir(".");

	return 0;
}






