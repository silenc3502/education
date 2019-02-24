#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#define BUF_SIZE		32

void find_replace_idx(int rfd, char *tstr, int *idx, int *dist)
{
	char buf[BUF_SIZE] = {0};
	int tlen = strlen(tstr);
	int loop_cnt = 0;
	int find_cnt = 0;
	int nr;
	int i;

	while(nr = read(rfd, buf, sizeof(buf)))
	{
		for(i = 0; i < nr; i++)
		{
			if(!strncmp(&buf[i], tstr, tlen))
			{
				idx[find_cnt++] = BUF_SIZE * loop_cnt + i;
				i += 4;

				if(find_cnt > 1)
					dist[find_cnt - 2] = idx[find_cnt - 1] - idx[find_cnt - 2];
			}

		}

		loop_cnt++;
	}
}

int check_idx(int loop_cnt, int *idx)
{
	int i, cnt = 0;

	for(i = 0; idx[i]; i++)
	{
		if(idx[i] < (loop_cnt + 1) * BUF_SIZE)
		{
			cnt++;
		}
		else
		{
			return cnt;
		}
	}

	return cnt;
}

void replace_text(int rfd, int wfd, char **str, int *idx, int *dist)
{
	char buf[BUF_SIZE] = {0};
	int tlen = strlen(str[1]);
	int clen = strlen(str[2]);
	int find_cnt = 0;
	int loop_cnt = 0;
	int i, nr;

	lseek(rfd, 0, SEEK_SET);

	while(nr = read(rfd, buf, sizeof(buf)))
	{
		if((idx[find_cnt] > (loop_cnt + 1) * BUF_SIZE) || !idx[find_cnt])
			write(wfd, buf, nr);
		else
		{
			int check_number = check_idx(loop_cnt, idx);
			int bypass_len = idx[find_cnt] - (loop_cnt * BUF_SIZE);
			//printf("check_number = %d\n", check_number);

			write(wfd, buf, bypass_len);

			for(i = 0; i < check_number; i++)
			{
				write(wfd, str[2], clen);
				//lseek(rfd, idx[find_cnt] + tlen, SEEK_SET);
				if(dist[find_cnt])
					write(wfd, &buf[bypass_len + tlen], dist[find_cnt++] - tlen);
				else
#if 1
					write(wfd, &buf[idx[find_cnt++] + tlen - BUF_SIZE * loop_cnt], BUF_SIZE * (loop_cnt + 1) - idx[find_cnt] - tlen);
#else
				{
					write(wfd, &buf[idx[find_cnt++] + tlen - BUF_SIZE * loop_cnt], 4);
					//write(wfd, &buf[idx[find_cnt] + tlen + 1 - BUF_SIZE * loop_cnt], 1);
					//write(wfd, &buf[idx[find_cnt] + tlen + 2- BUF_SIZE * loop_cnt], 1);
					//write(wfd, &buf[idx[find_cnt++] + tlen + 3- BUF_SIZE * loop_cnt], 1);
				}
				//write(wfd, &buf[idx[find_cnt] + tlen], 
#endif
			}

			//write(wfd, &buf[
		}

		loop_cnt++;
	}

	//printf("buf = %s\n", buf);
}

int main(int argc, char **argv)
{
	int fd;
	int sfd;
	long pos;
	int idx[BUF_SIZE] = {0};
	int dist[BUF_SIZE] = {0};

	if(argc != 3)
	{
		printf("Usage: exe target_text changing_txt\n");
		exit(-1);
	}

	if((sfd = open("tmp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
	{
		printf("Can't create tmp.txt\n");
	}
	if((fd = open("test.txt", O_RDWR)) < 0)
	{
		printf("There are no test.txt\n");
		exit(-1);
	}

	//replace_text(fd, sfd, argv[1], argv[2]);
	find_replace_idx(fd, argv[1], idx, dist);
	replace_text(fd, sfd, argv, idx, dist);

	close(fd);
	close(sfd);

	remove("test.txt");
	rename("tmp.txt", "test.txt");

	return 0;
}
