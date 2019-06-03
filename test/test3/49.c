#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>

char *rand_name(void)
{
        int i, len;
        static char buf[8] = "\0";

        memset(buf, 0, sizeof(buf));
        len = rand() % 4 + 4;

        for(i = 0; i < len; i++)
                buf[i] = rand() % 26 + 97;

        printf("buf = %s\n", buf);

        return buf;
}

void make_rand_dname(char **dname)
{
        int i;

        for(i = 0; i < 3; i++)
        {
                dname[i] = (char *)malloc(sizeof(char) * 8);
                strcpy(dname[i], rand_name());
        }
}

void make_rand_file(void)
{
        int i, j, fd, len, cnt;
        char buf[11] = "\0";

        len = rand() % 6 + 5;
        cnt = rand() % 4 + 2;

        for(i = 0; i < cnt; i++)
        {
                for(j = 0; j < len; j++)
                        buf[j] = rand() % 26 + 97;

                fd = open(buf, O_CREAT, 0644);
                close(fd);

                memset(buf, 0, sizeof(buf));
        }
}

void lookup_dname(char **dname)
{
        int i;

        for(i = 0; i < 3; i++)
        {
                chdir(dname[i]);
                make_rand_file();
                chdir("..");
        }
}

void find_abc(void)
{
        struct dirent *p;
        struct stat buf;
        DIR *dp;
        int i, len;

        dp = opendir(".");

        while(p = readdir(dp))
        {
                stat(p->d_name, &buf);
                len = strlen(p->d_name);

                for(i = 0; i < len; i++)
                {
                        if(!strncmp(&p->d_name[i], "a", 1) ||
                           !strncmp(&p->d_name[i], "b", 1) ||
                           !strncmp(&p->d_name[i], "c", 1))
                        {
                                printf("name = %s\n", p->d_name);
                        }
                }
        }

        closedir(dp);
}

void recur_find(char **dn)
{
        int i;

        for(i = 0; i < 3; i++)
        {
                chdir(dn[i]);
                find_abc();
                chdir("..");
        }
}

int main(void)
{
        int i;
        char *dname[3] = {0};

        srand(time(NULL));
        make_rand_dname(dname);

        for(i = 0; i < 3; i++)
                mkdir(dname[i], 0755);

        lookup_dname(dname);
        recur_find(dname);

        return 0;
}
