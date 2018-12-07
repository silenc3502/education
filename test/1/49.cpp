#include <iostream>

using namespace std;

class Queue{
private:
	int data;
	Queue *link;

public:
	Queue(int);
	void enQueue(int);
};

Queue::Queue(int data){
	this->data = data;
	link = NULL;
}

void Queue::enQueue(int d){
	Queue **tmp = &link;

	while(*tmp)
		*tmp = (*tmp)->link;

	*tmp = new Queue(d);
}

int main(void){
	Queue *queue = new Queue(10);
	queue->enQueue(20);

	return 0;
}
