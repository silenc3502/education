#include <stdio.h>
#include <fcntl.h>

#define MAX_BUFFER      26
char bin[MAX_BUFFER];
char bout[MAX_BUFFER];

int main(void)
{
        int fd, i, c = 65; 
        int write_ret, read_ret;

        if((fd = open("/dev/mydevicefile", O_RDWR)) < 0)
        {
                perror("open()");
                return -1; 
        }

        write_ret = write(fd, bout, 10);
        read_ret = read(fd, bin, 5); 

        printf("write_ret = %d, read_ret = %d\n", write_ret, read_ret);

        close(fd);
        return 0;
}
