#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define	VAR_SEPARATE			1
#define EXACT					2
#define STANDARD				4

typedef struct exp_tree et;

struct exp_tree
{
	char tokken[32];
	int len;
	et *left;
	et *right;
};

et *root;

void solve(char *str)
{
	int str_cnt = 0, num_cnt = 0;
	char c;
	char str_buf[32] = {0};
	char num_buf[32] = {0};

	while(c = *str++)
	{
		switch(c)
		{
			case '+':
				printf("+ detect\n");
				break;

			case '-':
				printf("- detect\n");
				break;

			case '*':
				printf("* detect\n");
				break;

			case '/':
				printf("/ detect\n");
				break;

			case '^':
				printf("^ detect\n");
				break;

			case '=':
				printf("= detect\n");
				break;

			case ' ':
				printf("white space detect\n");
				break;

			default:
				if((c > 0x61 && c < 0x7a) || (c > 0x41 && c < 0x5a))
					str_buf[str_cnt++] = c;

				if(c > 0x30 && c < 0x39)
					num_buf[num_cnt++] = c;

				break;
		}
	}
}

int main(void)
{
	solve("y = x + 3");
	solve("y' - 3y = 24");
	solve("3y' - 9y = 27");
	solve("y' - 12y = 24");
	solve("y'' + 5y' + 6y = 0");
	solve("xy^2 + (x^2 * y + 3)y' = 0");

	return 0;
}
