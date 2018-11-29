#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct __queue
{
	int data;
	struct __queue *link;
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
	queue **tmp = head;

	while(*tmp)
		tmp = &(*tmp)->link;

	*tmp = get_node();
	(*tmp)->data = data;
}

void print_queue(queue *head)
{
	queue *tmp = head;

	while(head)
	{
		printf("head->data = %d\n", head->data);
		head = head->link;
	}
}

void dequeue(queue **head, int data)
{
	queue **tmp = head;
	queue **backup = tmp;

	if(*tmp == NULL)
	{
finish:
		printf("There are no data that you delete\n");
		return;
	}

	while((*tmp)->data != data)
	{
		if((*tmp)->link)
		{
			backup = &(*tmp)->link;
			tmp = &(*tmp)->link;
		}
		else
			goto finish;
	}

	printf("Now you delete %d\n", data);
	free(*tmp);
	*backup = (*tmp)->link;
}

int main(void)
{
	int i;

	queue *head = NULL;

	srand(time(NULL));

	for(i = 0; i < 7; i++)
		enqueue(&head, (i + 1) * 10);

	print_queue(head);

	dequeue(&head, 10);
	print_queue(head);
	dequeue(&head, 30);
	dequeue(&head, 77);

	print_queue(head);

	return 0;
}
