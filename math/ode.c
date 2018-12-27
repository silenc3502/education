#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define	VAR_SEPARATE			1
#define EXACT					2
#define STANDARD				4

typedef struct exp_tree et;

struct exp_tree
{
	char tokken[32];
	et *left;
	et *right;
};

et *root;

void make_equal_exp_tree(void)
{
	root = (et *)malloc(sizeof(et));

	root->left = NULL;
	root->right = NULL;
	root->tokken[0] = '=';
}

et *make_exp_tree(char *str, int len)
{
	et *tmp = (et *)malloc(sizeof(et));

	tmp->left = NULL;
	tmp->right = NULL;
	memcpy(tmp->tokken, str, len);

	return tmp;
}

int find_back_len(char *str)
{
	int i, cnt = 0;

	for(i = 0; str[i]; i++)
		cnt++;

	return cnt;
}

int check_ode_type(void)
{
	int i, cnt = 0;
	char alpha_buf[28] = {0};

	for(i = 0; root->left->tokken[i]; i++)
		alpha_buf[root->left->tokken[i] - 65]++;

	for(i = 0; i < 27; i++)
		if(alpha_buf[i])
			cnt++;

	if(cnt == 1)
		return STANDARD;
	else
		// TODO
		return 137;
}

void solve(char *str)
{
	int i, eq_cnt = 0;
	char tmp[64] = {0};
	int type;
	int back_len;

	printf("start about = %s\n", str);

	for(i = 0; str[i]; i++)
	{
		tmp[i] = str[i];

		if(str[i] == '=')
		{
			make_equal_exp_tree();
			root->left = make_exp_tree(tmp, i - 1);
			back_len = find_back_len(&str[i + 2]);
			//printf("back_len = %d\n", back_len);
			root->right = make_exp_tree(&str[i + 2], back_len);
			eq_cnt++;
			break;
		}

	}

	if(!eq_cnt)
	{
		printf("Input: Wrong Format\n");
		return;
	}

	type = check_ode_type();
	switch(type)
	{
		case VAR_SEPARATE:
			break;

		case EXACT:
			break;

		case STANDARD:
			printf("This is Standard Type\n");
			break;

		default:
			printf("Not Implemented\n");
			break;
	}
}

int main(void)
{
	solve("y' + 2xy = 0");
	solve("y' - 3y = 24");
	solve("xy^2 + (x^2 * y + 3)y' = 0");
	solve("y' + 3");

	return 0;
}
