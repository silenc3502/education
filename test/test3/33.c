#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int save_area[1024];

int main(int argc, char **argv)
{
    int i;
    int ret;
    int index;
    int fd;
    char buf[1024] = {0};
    fd = open(argv[1], O_RDONLY);
    ret = read(fd, buf, sizeof(buf));
    for(i = 0, index = 1; buf[i]; i++)
    {
        if(buf[i] == '\n')
        {
            save_area[index] = i;
            index++;
        }
    }
    printf("Front 5 Lines\n");
    write(0, buf, save_area[5]);
    printf("\nBack 5 Lines\n");
    printf("%s", &buf[save_area[index - 6] + 1]);
    return 0;
}
