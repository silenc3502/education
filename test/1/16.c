#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void make_rand_num(int *data)
{
	int i, j, tmp, cnt = 0;

	for(i = 0; i < 10; i++)
	{
redo:
		tmp = rand() % 33 + 1;
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

int main(void)
{
	int i;
	int num;
	int data[10] = {0};

	queue *head = NULL;
	tree *root = NULL;

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

	return 0;
}
