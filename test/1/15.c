#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
	int data;
	struct node *link;
} queue;

queue *get_node(void)
{
	queue *tmp;
	tmp = (queue *)malloc(sizeof(queue));
	tmp->link = NULL;
	return tmp;
}

void enqueue(queue **head, int data)
{
	if(!(*head))
	{
		*head = get_node();
		(*head)->data = data;
		return;
	}

	enqueue(&(*head)->link, data);
}

void print_queue(queue *head)
{
	queue *tmp = head;

	while(tmp)
	{
		printf("tmp->data = %d\n", tmp->data);
		tmp = tmp->link;
	}

	printf("\n");
}

queue *chg_node(queue *head)
{
	queue *tmp;
	tmp = head;
	head = head->link;
	free(tmp);
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
	int data[10] = {0};
	queue *head = NULL;

	srand(time(NULL));

	memset(data, -1, sizeof(data));
	make_rand_num(data);
	print_data(data);

	for(i = 0; i < 10; i++)
		enqueue(&head, data[i]);

	print_queue(head);

	return 0;
}
