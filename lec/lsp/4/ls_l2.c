#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char **argv)
{
	char perm[11] = "----------";
	struct passwd *pw;
	struct group *gr;
	struct stat buf;
	char rwx[4] = "rwx";
	int i;

	if(argc != 2)
	{
		printf("Usage: exe filename or dirname\n");
		exit(-1);
	}

	stat(argv[1], &buf);

	if(S_ISDIR(buf.st_mode))
		perm[0] = 'd';
	else if(S_ISREG(buf.st_mode))
		perm[0] = '-';
	else if(S_ISFIFO(buf.st_mode))
		perm[0] = 'p';
	else if(S_ISCHR(buf.st_mode))
		perm[0] = 'c';
	else if(S_ISBLK(buf.st_mode))
		perm[0] = 'b';

	for(i = 0; i < 9; i++)
	{
		if((buf.st_mode >> (8 - i)) & 1)
		{
			perm[i + 1] = rwx[i % 3];
		}
	}

	printf("%s ", perm);

	pw = getpwuid(buf.st_uid);
	printf("%s ", pw->pw_name);

	gr = getgrgid(buf.st_gid);
	printf("%s\n", gr->gr_name);

	return 0;
}









