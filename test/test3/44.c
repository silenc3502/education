#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
        if(argc != 2)
        {
                printf("Usage: exe dir_name\n");
                exit(-1);
        }

        mkdir(argv[1], 0755);

        return 0;
}
