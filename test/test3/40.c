#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

char buf[1024];
int starting_val = 1;
int needs_clap;

void gameover(int signo)
{
    printf("\nGame Over!!!\n");
    exit(0);
}

void clap(void)
{
    printf("\nClap!\n");
    needs_clap--;
}

int find_parm(void)
{
    int i;
    int parm = 0;
    for(i = 0; ; i++)
        if(starting_val < pow(10, i))
            break;

    return parm = i;
}

void counting_clap(int signo)
{
    int i;
    int flag;
    int buf_len;

    if(needs_clap == 0)
    {
        flag = 1;
        buf_len = find_parm();
        for(i = 0; i < buf_len; i++)
        {
            if(i == 0)
                buf[i] = starting_val % (int)pow(10, i + 1);
            else
            {
                buf[i] = starting_val - buf[0];
                buf[i] /= pow(10, i);
            }
        }
        starting_val++;
    }

    if(flag == 1)
        for(i = 0; i < buf_len; i++)
            if(buf[i] == 3 || buf[i] == 6 || buf[i] == 9)
                needs_clap++;

    if(needs_clap)
    {
        flag = 0;
        clap();
    }
    else
        gameover(0);
}

int main(void)
{
    int i;
    int ret;
    int cmp;
    int buf_len;

    signal(SIGALRM, gameover);
    signal(SIGINT, counting_clap);

for(;;)
    {
        alarm(3);
        ret = read(0, buf, sizeof(buf));
        buf[ret - 1] = 0;
        buf_len = find_parm();

        for(i = 0; i < buf_len; i++)
            if(buf[i] == '3' || buf[i] == '6' || buf[i] == '9')
                gameover(0);

        cmp = atoi(buf);

        if(starting_val != cmp)
            gameover(0);
        starting_val++;
    }

    return 0;
}


