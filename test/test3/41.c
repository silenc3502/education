#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int flag;

char *check_text(char *text)
{
        int i;
        static char filename[1024];
        int text_len = strlen(text);
        if(text[0] != 'c' && text[1] != ' ')
                return NULL;
        if(text[text_len - 1] != 'c' && text[text_len - 2] != '.')
                return NULL;
        for(i = 2; i < text_len - 2; i++)
        {
                if(text[i] == ' ' || text[i] == '\t')
                        return NULL;
                filename[i - 2] = text[i];
        }
        strcat(filename, ".c");
        return filename;
}

int main(void)
{
        int fo;
        int fd, ret;
        char buf[1024];
        char *string = NULL;
        fd = open("myfifo", O_RDWR);
        fcntl(0, F_SETFL, O_NONBLOCK);
        fcntl(fd, F_SETFL, O_NONBLOCK);
        for(;;)
        {
                if((ret = read(0, buf, sizeof(buf))) > 0)
                {
                        buf[ret - 1] = 0;
                        printf("Keyboard Input : [%s]\n", buf);
                        string = check_text(buf);
                        printf("String : %s\n", string);
                }
                if((ret = read(fd, buf, sizeof(buf))) > 0)
                {
                        buf[ret - 1] = 0;
                        printf("Pipe Input : [%s]\n", buf);
                        string = check_text(buf);
                        printf("String : %s\n", string);
                }
                fo = open(string, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                close(fo);
        }
        close(fd);
        return 0;
}
