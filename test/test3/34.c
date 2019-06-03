#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

void recursive_dir(char *dname);

int main(int argc, char **argv)
{
    recursive_dir(".");
    return 0;
}

void recursive_dir(char *dname)
{
    struct dirent *p;
    struct stat buf;
    DIR *dp;
    chdir(dname);
    dp = opendir(".");
    printf("\t%s : \n", dname);
    while(p = readdir(dp))
        printf("%s\n", p -> d_name);
    rewinddir(dp);
    while(p = readdir(dp))
    {
        stat(p -> d_name, &buf);
        if(S_ISDIR(buf.st_mode))
            if(strcmp(p -> d_name, ".") && strcmp(p -> d_name, ".."))
                recursive_dir(p -> d_name);
    }
    chdir("..");
    closedir(dp);
}
