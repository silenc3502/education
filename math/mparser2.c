#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define	VAR_SEPARATE			1
#define EXACT					2
#define STANDARD				4

enum tree_type
{
	MINUS = 1,
	STR = 2,
	PLUS = 4,
	NUM = 8,
	EQUAL = 16,
	MULT = 32,
	DIVIDE = 64,
	DIRIVATIVE = 128,
};

typedef enum tree_type tt;

typedef struct exp_tree et;

struct exp_tree
{
	char tokken[32];
	int type;
	int len;
	et *left;
	et *right;
};

et *root;
et *right;
et *after_equal;

bool need_right;

et *make_et_root(void)
{
	et *tmp;
	tmp = (et *)malloc(sizeof(et));

	memset(tmp->tokken, 0x0, sizeof(tmp->tokken));

	tmp->left = NULL;
	tmp->right = NULL;

	return tmp;
}

void push_str_et(et **target, char *str_buf, int len, tt type)
{
	et *tmp = NULL;
	//et *tmp = *target;
	//*target = make_et_root();
	//strncpy((*target)->tokken, str_buf, len);

	if(tmp && tmp->left)
	{
		tmp = make_et_root();
		strncpy(tmp->tokken, str_buf, len);
		(*target)->right = tmp;
	}
	else
	{
		tmp = *target;
		*target = make_et_root();
		strncpy((*target)->tokken, str_buf, len);
		(*target)->left = tmp;
	}

	(*target)->type = type;
	//(*target)->type = STR;
	//(*target)->right = tmp;
}

void push_num_et(et **target, char *num_buf, int len)
{
	et *tmp = *target;

	if(!tmp)
	{
		*target = make_et_root();
		strncpy((*target)->tokken, num_buf, len);
		(*target)->left = tmp;
	}
	else if(tmp->type & (PLUS | MINUS | MULT | DIVIDE | DIRIVATIVE))
	{
		(*target)->right = make_et_root();
		strncpy((*target)->right->tokken, num_buf, len);
		//tmp->right = *target;
	}
	else
		(*target)->left = tmp;

	(*target)->type = NUM;
}

int read_non_ws(char *str_buf, char *str)
{
	int i;

	for(i = 0; ; i++)
	{
		if(*str == ' ' || *str == '\n')
			break;

		*str++;
	}

	strncpy(str_buf, str - i, i);

	return i;
}

void solve(char *str)
{
	int str_cnt = 0, num_cnt = 0;

	char c, p;
	char str_buf[32] = {0};
	char num_buf[32] = {0};

	bool str_flag = false, num_flag = false, find_equal = false;

	while(c = *str++)
	{
		switch(c)
		{
			case '+':
#if 0
				if(find_equal)
					push_str_et(&after_equal, "+", 1, PLUS);
				else
					push_str_et(&root, "+", 1, PLUS);
#endif
				push_str_et(&root, "+", 1, PLUS);

				need_right = true;

				printf("+ detect\n");
				break;

			case '-':
				printf("- detect\n");
				need_right = true;
				break;

			case '*':
				printf("* detect\n");
				need_right = true;
				break;

			case '/':
				printf("/ detect\n");
				need_right = true;
				break;

			case '^':
				printf("^ detect\n");
				need_right = true;
				break;

			case '=':
				push_str_et(&root, "=", 1, EQUAL);
				printf("= detect\n");
				find_equal = true;
				need_right = true;
				break;

			case ' ':
				printf("white space detect\n");
				break;

			case '\n':
				printf("finish line detect\n");
				break;

			case 'a' ... 'z':
			case 'A' ... 'Z':
			case '0' ... '9':
				*str--;
				str += read_non_ws(str_buf, &(*str));

#if 0
				if(root->left)
					push_str_et(&right, str_buf, strlen(str_buf), STR);
				else
					push_str_et(&root, str_buf, strlen(str_buf), STR);
#endif
				push_str_et(&root, str_buf, strlen(str_buf), STR);

			default:
				break;
#if 0
				if((c > 0x61 && c < 0x7a) || (c > 0x41 && c < 0x5a))
				{
					str_buf[str_cnt++] = c;
					str_flag = true;
				}
				else if(c > 0x30 && c < 0x39)
				{
					num_buf[num_cnt++] = c;
					num_flag = true;
				}

				while(p = *str++)
				{
					if((p > 0x61 && p < 0x7a) || (p > 0x41 && p < 0x5a))
					{
						if(str_flag)
							str_buf[str_cnt++] = p;
						else
						{
							if(find_equal)
								push_str_et(&after_equal, str_buf, str_cnt, STR);
							else
								push_str_et(&root, str_buf, str_cnt, STR);

							memset(str_buf, 0x0, sizeof(str_buf));
							str_cnt = 0;
						}
					}

					if(p > 0x30 && p < 0x39)
					{
						if(num_flag)
							num_buf[num_cnt++] = p;
						else
						{
							if(find_equal)
								push_num_et(&after_equal, num_buf, num_cnt);
							else
								push_num_et(&root, num_buf, num_cnt);

							memset(num_buf, 0x0, sizeof(num_buf));
							num_cnt = 0;
						}
					}

					if(p == ' ' || p == '\n')
					{
						if(str_flag)
						{
							if(find_equal)
								push_str_et(&after_equal, str_buf, str_cnt, STR);
							else
								push_str_et(&root, str_buf, str_cnt, STR);

							memset(str_buf, 0x0, sizeof(str_buf));
							str_cnt = 0;
							str_flag = false;
						}
						else if(num_flag)
						{
							//push_num_et(&root, num_buf, num_cnt);
							if(find_equal)
								push_num_et(&after_equal, num_buf, num_cnt);
							else
								push_num_et(&root, num_buf, num_cnt);

							memset(num_buf, 0x0, sizeof(num_buf));
							num_cnt = 0;
							num_flag = false;
						}

						printf("white space detect\n");
						break;
					}
				}

				break;
#endif
		}
	}

	root->right = after_equal;
}

void print_math_tree(et *root)
{
	et *tmp = root;

	if(tmp)
	{
		print_math_tree(tmp->left);
		printf("%s", tmp->tokken);
		print_math_tree(tmp->right);
	}
}

int main(void)
{
	//root = make_exp_tree_root();

	solve("y = x + 3\n");
	print_math_tree(root);
	printf("\n");

#if 0
	solve("y' - 3y = 24\n");
	print_math_tree(root);
	printf("\n");

	solve("3y' - 9y = 27\n");
	solve("y' - 12y = 24\n");
	solve("y'' + 5y' + 6y = 0\n");
	solve("xy^2 + (x^2 * y + 3)y' = 0\n");
#endif

	return 0;
}
