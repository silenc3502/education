#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

void skip_white_space(char *buf)
{
	int i;

	for(i = 0; buf[i] != ' '; i++)
		;
}

long replace_text(int rfd, int wfd, char *tstr, char *cstr)
{
	char buf[32] = {0};
	int tlen = strlen(tstr);
	int clen = strlen(cstr);
	int loop_cnt = 0;
	int find_cnt = 0;
	int backup = 0, flag;
	int idx;
	int nr;
	int i;

	while(nr = read(rfd, buf, sizeof(buf)))
	{
		for(i = 0; i < nr; i++)
		{
			if(!strncmp(&buf[i], tstr, tlen))
			{
				if(!flag)
				{
					write(wfd, buf, i);
					backup = i;
				}

				//lseek(wfd, (off_t)i + (32 * loop_cnt) - find_cnt, SEEK_SET);
				skip_white_space(buf);
				write(wfd, cstr, clen);
				write(wfd, &buf[i + tlen], 1);
				i += 4;
				find_cnt++;
				flag = 1;
			}
		}

		if(flag)
		{
			int spec_len = backup + (tlen + 1) * find_cnt;
			write(wfd, &buf[spec_len], nr - spec_len);
			flag = 0;
			continue;
		}

		write(wfd, buf, nr);

		loop_cnt++;
	}
}

int main(int argc, char **argv)
{
	int fd;
	int sfd;
	long pos;

	if(argc != 3)
	{
		printf("Usage: exe target_text changing_txt\n");
		exit(-1);
	}

	sfd = open("test.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if((fd = open("reading2.txt", O_RDWR)) < 0)
	{
		printf("There are no reading2.txt\n");
		exit(-1);
	}

	pos = replace_text(fd, sfd, argv[1], argv[2]);

	close(fd);

	return 0;
}




