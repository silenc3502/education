#include <sys/wait.h>

int main(void)
{
    pid_t pid;
    int status;
    if((pid = fork()) > 0)
    {
        wait(&status);
        if((status & 0xff) == 0)
            printf("(정상 종료)status : 0x%x\n", WEXITSTATUS(status));
        else if(((status >> 8) & 0xff) == 0)
            printf("(비정상 종료)status : 0x%x\n", status & 0x7f);
    }
    else if(pid == 0)
        abort();
    else
    {
        perror("fork() ");
        exit(-1);
    }
    return 0;
}
