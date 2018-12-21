#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLACK   0
#define RED     1

typedef struct _rb_tree rb_tree;
typedef struct _rb_node rb_node;

struct _rb_node
{
	int data;
	int color;

	rb_node *left;
	rb_node *right;
	rb_node *parent;
};

struct _rb_tree
{
	rb_node *root;
	rb_node *nil;
};

typedef struct node
{
	int data;
	struct node *link;
} queue;

typedef struct t
{
	int data;
	struct t *l;
	struct t *r;
} tree;

queue *get_queue_node(void)
{
	queue *tmp;
	tmp = (queue *)malloc(sizeof(queue));
	tmp->link = NULL;
	return tmp;
}

tree *get_node(void)
{
	tree *tmp = (tree *)malloc(sizeof(tree));
	tmp->l = NULL;
	tmp->r = NULL;
	return tmp;
}

void enqueue(queue **head, int data)
{
	if(!(*head))
	{
		*head = get_queue_node();
		(*head)->data = data;
		return;
	}

	enqueue(&(*head)->link, data);
}

void tree_ins(tree **root, int data)
{
	if(!(*root))
	{
		*root = get_node();
		(*root)->data = data;
		return;
	}
	if((*root)->data > data)
		tree_ins(&(*root)->l, data);
	else
		tree_ins(&(*root)->r, data);
}

void print_queue(queue *head)
{
	queue *tmp = head;

	printf("Queue:\n");

	while(tmp)
	{
		printf("tmp->data = %d\n", tmp->data);
		tmp = tmp->link;
	}

	printf("\n");
}

void print_tree(tree *root)
{
	if(root)
	{
		printf("data = %d\n", root->data);
		print_tree(root->l);
		print_tree(root->r);
	}
}

queue *chg_queue_node(queue *head)
{
	queue *tmp;
	tmp = head;
	head = head->link;
	free(tmp);
	return head;
}

queue *dequeue(queue *head, int *num)
{
	if(!head)
	{
		printf("Can't find it!\n");
		return NULL;
	}
	else if(!(head->data % 2))
		head->link = dequeue(head->link, num);
	else
	{
		*num = head->data;
		head = chg_queue_node(head);
	}

	return head;
}

queue *get_data(queue *head, int *num)
{
	if(!head)
	{
		printf("There are no data\n");
		return NULL;
	}
	else
	{
		*num = head->data;
		head = chg_queue_node(head);
	}

	return head;
}

void make_rand_num(int *data)
{
	int i, j, tmp, cnt = 0;

	for(i = 0; i < 10; i++)
	{
redo:
		tmp = rand() % 10 + 1;
		printf("Entering: tmp = %d, i = %d\n", tmp, i);
		for(j = 0; j < cnt; j++)
		{
			printf("Entering: j = %d, cnt = %d\n", j, cnt);
			if(tmp == data[j])
			{
				printf("Duplication\n");
				goto redo;
			}
		}
		//printf("data[%d] = %d\n", i, data[i]);
		data[i] = tmp;
		cnt++;
	}
}

void print_data(int *data)
{
	int i;

	for(i = 0; i < 10; i++)
		printf("data[%d] = %d\n", i, data[i]);
}

void rb_left_rot(rb_tree **tree, rb_node *x)
{
	rb_node *y;
	rb_node *nil = (*tree)->nil;

	y = x->right;
	x->right = y->left;

	if (y->left != nil)
		y->left->parent = x;

	y->parent = x->parent;

	if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;

	y->left = x;
	x->parent = y;
}

void rb_right_rot(rb_tree **tree, rb_node *y)
{
	rb_node *x;
	rb_node *nil = (*tree)->nil;

	x = y->left;
	y->left = x->right;

	if (nil != x->right)
		x->right->parent = y;

	x->parent = y->parent;

	if (y->parent->left == y)
		y->parent->left = x;
	else
		y->parent->right = x;

	x->right = y;
	y->parent = x;
}

void rb_tree_ins_helper(rb_tree **tree, rb_node *z)
{
	rb_node *x;
	rb_node *y;
	rb_node *nil = (*tree)->nil;

	z->left = z->right = nil;
	y = (*tree)->root;
	x = (*tree)->root->left;

	while (x != nil)
	{
		y = x;

		if (x->data > z->data)
			x = x->left;
		else
			x = x->right;
	}

	z->parent = y;

	if (((*tree)->root == y) || (y->data > z->data))
		y->left = z;
	else
		y->right = z;
}

rb_node *rb_tree_ins(rb_tree **tree, int data)
{
	rb_node *y;
	rb_node *x;
	rb_node *tmp;

	x = (rb_node *)malloc(sizeof(rb_node));
	x->data = data;

	rb_tree_ins_helper(tree, x);

	tmp = x;
	x->color = RED;

	while (x->parent->color)
	{
		if (x->parent == x->parent->parent->left)
		{
			y = x->parent->parent->right;

			if (y->color)
			{
				x->parent->color = BLACK;
				y->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else
			{
				if (x->parent->right == x)
				{
					x = x->parent;
					rb_left_rot(tree, x);
				}

				x->parent->color = BLACK;
				x->parent->parent->color = RED;

				rb_right_rot(tree, x->parent->parent);
			}
		}
		else
		{
			y = x->parent->parent->left;

			if (y->color)
			{
				x->parent->color = BLACK;
				y->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else
			{
				if (x->parent->left == x)
				{
					x = x->parent;

					rb_right_rot(tree, x);
				}

				x->parent->color = BLACK;
				x->parent->parent->color = RED;

				rb_left_rot(tree, x->parent->parent);
			}
		}
	}

	(*tree)->root->left->color = BLACK;

	return tmp;
}

rb_tree *rb_tree_create(void)
{
	rb_tree *rbtree;
	rb_node *tmp;

	rbtree = (rb_tree *)malloc(sizeof(rb_tree));

	tmp = rbtree->nil = (rb_node *)malloc(sizeof(rb_node));
	tmp->parent = tmp->left = tmp->right = tmp;
	tmp->color = BLACK;
	tmp->data = 0;

	tmp = rbtree->root = (rb_node *)malloc(sizeof(rb_node));
	tmp->parent = tmp->left = tmp->right = rbtree->nil;
	tmp->color = BLACK;
	tmp->data = 0;

	return rbtree;
}

void rb_tree_inorder_print(rb_tree *tree, rb_node *x)
{
	rb_node *nil = tree->nil;
	rb_node *root = tree->root;

	if (x != tree->nil)
	{
		rb_tree_inorder_print(tree, x->left);

		printf("Data = %4i ", x->data);
		printf("Left Data = ");

		if (x->left == nil)
			printf("NULL ");
		else
			printf("%4i ", x->left->data);

		printf("Right Data = ");

		if (x->right == nil)
			printf("NULL ");
		else
			printf("%4i ", x->right->data);

		printf("Parent Data = ");

		if (x->parent == root)
			printf("NULL ");
		else
			printf("%4i ", x->parent->data);

		printf("Color = %4i\n", x->color);

		rb_tree_inorder_print(tree, x->right);
	}
}

void rb_tree_print(rb_tree *tree)
{
	rb_tree_inorder_print(tree, tree->root->left);
}

int main(void)
{
	int i;
	int num;
	int data[10] = {0};

	queue *head = NULL;
	tree *root = NULL;
	rb_tree *rbtree = NULL;

	srand(time(NULL));

	memset(data, -1, sizeof(data));
	make_rand_num(data);
	print_data(data);

	for(i = 0; i < 10; i++)
		enqueue(&head, data[i]);

	print_queue(head);

	for(i = 0; i < 10; i++)
	{
		head = dequeue(head, &num);
		printf("num = %d\n", num);
		if(num)
		{
			tree_ins(&root, num);
			num = 0;
		}
	}

	print_queue(head);
	print_tree(root);
	printf("\n");

	rbtree = rb_tree_create();

	for(i = 0; i < 5; i++)
	{
		head = get_data(head, &num);
		printf("num = %d\n", num);
		rb_tree_ins(&rbtree, num);
	}

	rb_tree_print(rbtree);
	printf("\n");

	return 0;
}
