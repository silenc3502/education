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
		alpha_buf[root->left->tokken[i] - 0x61]++;
#if 0
		alpha_buf[root->left->tokken[i] - 65]++;	// 이렇게하면 버스 에러 발생
#endif

	for(i = 0; i < 27; i++)
		if(alpha_buf[i])
			cnt++;

	if(cnt == 1)
		return STANDARD;
	else
		// TODO
		return 0;
}

void calc_int_param(char *int_param, char *idx_cache, char *left, int *coeff)
{
	int i;
	char px[32] = {0};

	for(i = 1; idx_cache[i]; i++)
	{
		if(left[idx_cache[i]] == 0x27)
			continue;
		else
			// 원래는 개수 파악이 필요하지만 그냥 구현함(3y O, 12y X)
			strncpy(px, &left[idx_cache[i] - 2], 1);
	}

	printf("px = %s\n", px);

	*coeff = atoi(px);

	sprintf(int_param, "e^%sx", px);
}

void solve_standard(void)
{
	int i, rval, coeff, left_len, right_len, cnt = 0, prime_cnt = 0;
	char int_param[32] = {0};
	char idx_cache[32] = {0};
	char left[32] = {0};
	char right[32] = {0};
	char loc[32] = {0};

	strcpy(left, root->left->tokken);
	strcpy(right, root->right->tokken);

	left_len = strlen(left);
	right_len = strlen(right);

	printf("left len = %d\n", left_len);
	printf("right len = %d\n", right_len);

	for(i = 0; i < left_len; i++)
	{
		if((left[i] > 0x61 && left[i] < 0x7a) || (left[i] > 0x41 && left[i] < 0x5a))
		{
			loc[i]++;
			idx_cache[cnt++] = i + 1;

			if(left[i + 1] == 0x27)
				prime_cnt++;
		}
	}

	if(prime_cnt != 1)
	{
		printf("Input: Wrong Format\n");
		return;
	}
	else
		printf("Normalization OK\n");

	calc_int_param(int_param, idx_cache, left, &coeff);
	printf("int_param = %s\n", int_param);

	rval = atoi(right);
	printf("coeff = %d\trval = %d\n", coeff, rval);
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
		printf("Input: Wrong Format\n\n");
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
			solve_standard();
			break;

		default:
			printf("Not Implemented\n\n");
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
