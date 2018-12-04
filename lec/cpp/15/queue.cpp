#include <stdlib.h>
#include <iostream>

using namespace std;

typedef struct __queue queue;
struct __queue
{
	int data;
	queue *link;
	void (*q)(queue **, int);
	queue (*(*get_q)(void));
	void (*dq)(queue **, int);
	void (*pq)(queue *);
};

queue *get_queue_node(void);
void dequeue(queue **, int);
void enqueue(queue **, int);
void print_queue(queue *);

queue *get_queue_node(void)
{
	queue *tmp = (queue *)malloc(sizeof(queue));

	tmp->q = enqueue;
	tmp->dq = dequeue;
	tmp->pq = print_queue;
	tmp->get_q = get_queue_node;

	tmp->link = NULL;

	return tmp;
}

void dequeue(queue **head, int data)
{
	queue *tmp = *head;

	if((*head)->data == data)
	{
		// printf("data = %d\n", (*head)->data);
		*head = (*head)->link;
		free(tmp);

		return;
	}

	(**head).dq(&(*head)->link, data);
}

void enqueue(queue **head, int data)
{
	cout << "enqueue called!!!" << endl;

	if(!(*head))
	{
		*head = get_queue_node();

#if 0
		(**head).q = enqueue;
		(**head).get_q = get_queue_node;
		(**head).dq = dequeue;
#endif

		(*head)->data = data;
		return;
	}

	(**head).q(&(*head)->link, data);
}

void print_queue(queue *head)
{
	queue *tmp = head;

	while(tmp)
	{
		cout << "data = " << tmp->data << endl;
		tmp = tmp->link;
	}
}

int main(void)
{
	int i;
	int arr[5] = {10, 30, 20, 40};

	queue *head = (queue *)malloc(sizeof(queue));

	head->data = 10;
	head->get_q = get_queue_node;
	head->q = enqueue;
	head->dq = dequeue;
	head->pq = print_queue;
	head->link = NULL;

	for(i = 2; i < 6; i++)
		(*head).q(&head, i * 10);
		//head->q(&head, i * 10);
		//enqueue(&head, i * 10);

	(*head).pq(head);

	for(i = 0; i < 2; i++)
		(*head).dq(&head, arr[i]);

	cout << "After Delete" << endl;
	(*head).pq(head);

	return 0;
}







