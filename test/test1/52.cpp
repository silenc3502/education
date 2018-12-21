#include <iostream>

using namespace std;

class Queue{
private:
	int data;
	Queue *link;

public:
	Queue(int);
	void enQueue(int);
	Queue *deQueue(int);
	void printQueue(void);
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

void Queue::printQueue(void){
	Queue *tmp = link;

	cout << "data = " << endl;
	cout << data << endl;

	while(tmp){
		cout << tmp->data << endl;
		tmp = tmp->link;
	}
}

Queue *Queue::deQueue(int d){
	Queue **tmp = &link;
	Queue **backup = tmp;

	if(data == d)
	{
		Queue *ret = link;
		delete this;
		return ret;
	}

	while((*tmp)->data != d){
		backup = &(*tmp)->link;
		tmp = &(*tmp)->link;
	}

	delete *tmp;
	(*backup) = (*tmp)->link;
	return this;
}

int main(void){
	Queue *queue = new Queue(10);
	queue->enQueue(20);
	queue->printQueue();
	queue = queue->deQueue(20);
	queue->printQueue();

	return 0;
}
