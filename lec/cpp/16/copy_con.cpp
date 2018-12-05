#include <iostream>

using namespace std;

class A
{
public:
	A(void);
	A(int i);
	A(const A& a);
};

A::A(void)
{
	cout << "Default Constructor" << endl;
}

A::A(int i)
{
	cout << "Default Constructor with Argument" << endl;
}

A::A(const A& a )
{
	cout << "Copy Constructor" << endl;
}

int main(void)
{
	A obj1;
	A obj2(33);
	A obj3(obj2);

	return 0;
}




