#include <iostream>

using namespace std;

class Test
{
	int data;

public:
	Test(void);
	void print(void);
	friend void setData(Test& t, int data);
};

Test::Test(void)
{
	cout << "Test called" << endl;
}

void Test::print(void)
{
	cout << "data = " << data << endl;
}

void setData(Test& t, int data)
{
	t.data = data;
}

int main(void)
{
	Test t;
	t.print();
	setData(t, 2018);
	t.print();

	return 0;
}



