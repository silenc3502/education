#include <iostream>

using namespace std;

typedef struct __list
{
	int data;
	struct __list *link;
	int (*p)(void);
	//(struct __list *)(*p)(void);
} l;

int test(void)
{
	cout << "test" << endl;
}

int main(void)
{
	l p = {0, NULL, test};
	p.p();

	return 0;
}
