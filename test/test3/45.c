#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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
                //dname[i] = rand_name();
        }
}

int main(void)
{
        int i;
        char *dname[3] = {0};

        srand(time(NULL));
        make_rand_dname(dname);

        for(i = 0; i < 3; i++)
        {
                printf("dname[%d] = %s\n", i, dname[i]);
                mkdir(dname[i], 0755);
        }

        return 0;
}
