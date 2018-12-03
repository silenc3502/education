#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct __tree
{
	int data;
	struct __tree *left;
	struct __tree *right;
} tree;

typedef struct __stack
{
	void *data;
	int idx;
} stack;

typedef struct __stack_manager
{
	int cur_idx;
	int elem_num;
	stack *arr;
} sm;

#if 0
stack *get_stack_node(void)
{
	stack *tmp;
	tmp = (stack *)malloc(sizeof(stack));
	tmp->link = NULL;
	return tmp;
}
#endif

tree *get_tree_node(void)
{
	tree *tmp;
	tmp = (tree *)malloc(sizeof(tree));
	tmp->left = NULL;
	tmp->right = NULL;
	return tmp;
}

#if 0
void *pop(stack **top)
{
	stack *tmp = *top;
	void *data = NULL;

	if(*top == NULL)
	{
		printf("stack is empty!\n");
		return NULL;
	}

	data = (*top)->data;
	*top = (*top)->link;
	free(tmp);

	//return (*top)->data;
	return data;
}
#endif

void *superfast_pop(sm *m)
{
	m->elem_num--;
	return m->arr[--m->cur_idx].data;
}

#if 0
void push(stack **top, void *data)
{
	if(data == NULL)
		return;

	stack *tmp = *top;
	*top = get_stack_node();
	(*top)->data = malloc(sizeof(void *));
	(*top)->data = data;
	(*top)->link = tmp;
}
#endif

void superfast_push(sm *m, void *data)
{
	if(data == NULL)
		return;

	m->arr[m->cur_idx++].data = data;
	m->elem_num++;

#if 0
	if(m->cur_idx)
		return;
	else
		;
#endif
}

void non_recur_tree_ins(tree **root, int data)
{
	tree **tmp = root;

	while(*tmp)
	{
		if((*tmp)->data > data)
			tmp = &(*tmp)->left;
		else if((*tmp)->data < data)
			tmp = &(*tmp)->right;
	}

	*tmp = get_tree_node();
	(*tmp)->data = data;
}

bool stack_is_not_empty(sm *m)
{
	if(m->elem_num)
		return true;
	else
		return false;
}

#if 0
bool stack_is_not_empty(stack *top)
{
	if(top != NULL)
		return true;
	else
		return false;
}
#endif

#if 0
void print_tree(tree **root)
{
	tree **tmp = root;
	stack *top = NULL;

	push(&top, *tmp);

	while(stack_is_not_empty(top))
	{
		tree *t = (tree *)pop(&top);
		tmp = &t;

		printf("data = %d, ", (*tmp)->data);

		if((*tmp)->left)
			printf("left = %d, ", (*tmp)->left->data);
		else
			printf("left = NULL, ");

		if((*tmp)->right)
			printf("right = %d\n", (*tmp)->right->data);
		else
			printf("right = NULL\n");

		push(&top, (*tmp)->right);
		push(&top, (*tmp)->left);
		
		//tmp = &(*tmp)->left;

		//*tmp = (tree *)pop(&top);
	}
}
#endif

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

void init_stack_manager(sm *m)
{
	stack *tmp = (stack *)malloc(sizeof(stack) * 128);
	memset(tmp, 0x0, sizeof(stack) * 128);

	(*m).arr = tmp;
	(*m).cur_idx = 0;
}

#if 0
stack *init_stack(void)
{
	stack *tmp = (stack *)malloc(sizeof(stack) * 128);

	memset(tmp, 0x0, sizeof(stack) * 128);

	return tmp;
}
#endif

void superfast_tree_print(tree **root, sm *m)
{
	tree **tmp = root;

#if 0
	stack *top = NULL;

	push(&top, *tmp);
#endif

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

int main(void)
{
	int i;

#if 0
	int data[14] = {50, 45, 73, 32, 48, 46, 16,
                      37, 120, 47, 130, 127, 124};
#endif

	int data[14] = {20, 10, 30, 50, 70, 60, 40, 90, 80, 100};

	sm manager = {0};
	tree *root = NULL;

	init_stack_manager(&manager);

	for(i = 0; data[i]; i++)
		non_recur_tree_ins(&root, data[i]);

	//print_tree(&root);
	superfast_tree_print(&root, &manager);

	non_recur_delete_tree(&root, 50);
	printf("After Delete\n");

	superfast_tree_print(&root, &manager);
	
	return 0;
}
