#include <stdio.h>
#include <stdlib.h>

typedef struct __queue
{
	int data;
	struct __queue *link;
} queue;

queue *get_queue_node(void)
{
	queue *tmp = (queue *)malloc(sizeof(queue));
	tmp->link = NULL;
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

void dequeue(queue **head, int data)
{
	queue *tmp = *head;

	if((*head)->data == data)
	{
		printf("data = %d\n", (*head)->data);
		*head = (*head)->link;
		free(tmp);

		return;
	}

	dequeue(&(*head)->link, data);
}

void print_queue(queue *head)
{
	queue *tmp = head;

	while(tmp)
	{
		printf("data = %d\n", tmp->data);
		tmp = tmp->link;
	}
}

int main(void)
{
	int i;
	int arr[5] = {10, 30, 20, 40};
	queue *head = NULL;

	for(i = 1; i < 5; i++)
		enqueue(&head, i * 10);

	print_queue(head);

	for(i = 0; i < 4; i++)
		dequeue(&head, arr[i]);

	return 0;
}







