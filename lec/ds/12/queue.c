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
	if(*head == NULL)
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

	while(head)
	{
		printf("head->data = %d\n", head->data);
		head = head->link;
	}
}

queue *dequeue(queue *head, int data)
{
	queue *tmp = head;

	if(tmp == NULL)
		printf("There are no data that you delete\n");

	if(head->data != data)
		head->link = dequeue(head->link, data);
	else
	{
		//queue *res = head->link;
		printf("Now you delete %d\n", data);
		free(tmp);
		return head->link;
	}

	return head;
}

int main(void)
{
	int i;

	queue *head = NULL;

	srand(time(NULL));

	for(i = 0; i < 3; i++)
		enqueue(&head, (i + 1) * 10);

	print_queue(head);

	head = dequeue(head, 10);

	print_queue(head);

	return 0;
}
