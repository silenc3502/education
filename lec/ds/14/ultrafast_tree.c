#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct __tree
{
	int data;
	int left_idx;
	int right_idx;
} tree;

typedef struct __tree_manager
{
	int cur_idx;
	int elem_num;
	int start_idx;
	tree *arr;
} tm;

void tree_ins(tm *m, int data)
{
	int idx = m->start_idx;

	while(m->arr[idx].data)
	{
		if(m->arr[idx].data > data)
			idx = m->arr[idx].left_idx;
		else if(m->arr[idx].data < data)
			idx = m->arr[idx].right_idx;
	}

	m->arr[idx].data = data;
	m->elem_num++;
	m->arr[idx].left_idx = ++m->cur_idx;
	m->arr[idx].right_idx = ++m->cur_idx;
}

#if 0
tree *chg_node(tree *root)
{
	tree *tmp = root;

	if(!root->right)
		root = root->left;
	else if(!root->left)
		root = root->right;

	free(tmp);

	return root;
}

void find_max(tree **root, int *data)
{
	tree **tmp = root;

	while(*tmp)
	{
		if((*tmp)->right)
			tmp = &(*tmp)->right;
		else
		{
			*data = (*tmp)->data;
			*tmp = chg_node(*tmp);
			break;
		}
	}
}

void non_recur_delete_tree(tree **root, int data)
{
	tree **tmp = root;
	int num;

	while(*tmp)
	{
		if((*tmp)->data > data)
			tmp = &(*tmp)->left;
		else if((*tmp)->data < data)
			tmp = &(*tmp)->right;
		else if((*tmp)->left && (*tmp)->right)
		{
			find_max(&(*tmp)->left, &num);
			(*tmp)->data = num;
			return;
		}
		else
		{
			(*tmp) = chg_node(*tmp);
			return;
		}
	}

	printf("Not Found\n");
}
#endif

void init_tree_manager(tm *m)
{
	tree *tmp = (tree *)malloc(sizeof(tree) * 128);
	memset(tmp, 0x0, sizeof(tree) * 128);

	(*m).arr = tmp;
	(*m).cur_idx = 0;
	(*m).start_idx = 0;
}

#if 0
void superfast_tree_print(tree **root, sm *m)
{
	tree **tmp = root;

	superfast_push(m, *tmp);

	while(stack_is_not_empty(m))
	{
		tree *t = (tree *)superfast_pop(m);
		tmp = &t;

#if 1
		printf("data = %d, ", (*tmp)->data);

		if((*tmp)->left)
			printf("left = %d, ", (*tmp)->left->data);
		else
			printf("left = NULL, ");

		if((*tmp)->right)
			printf("right = %d\n", (*tmp)->right->data);
		else
			printf("right = NULL\n");

		superfast_push(m, (*tmp)->right);
		superfast_push(m, (*tmp)->left);
#endif
	}
}
#endif

int main(void)
{
	int i;
	int data[14] = {20, 10, 30, 50, 70, 60, 40, 90, 80, 100};

	tm manager = {0};

	init_tree_manager(&manager);

	for(i = 0; data[i]; i++)
		tree_ins(&manager, data[i]);

	return 0;
}
