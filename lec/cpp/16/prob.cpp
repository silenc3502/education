#include <iostream>
#include <string.h>

using namespace std;

class Person{
private:
	char *name;
	char *phone;

public:
#ifdef __PROB__
	Person(char *n, char *p);
#endif
	Person(const Person& p);
	~Person(void);
	void showInfo(void);
};

#ifdef __PROB__
Person::Person(char *n, char *p){
	cout << "I'm Default Constructor" << endl;

	name = new char[strlen(n) + 1];
	strncpy(name, n, strlen(n));

	phone = new char[strlen(p) + 1];
	strncpy(phone, p, strlen(p));
}
#endif

//#ifndef __NOT__
Person::Person(const Person& p){
	cout << "I'm Copy Constructor" << endl;

	name = new char[strlen(p.name) + 1];
	strncpy(name, p.name, strlen(p.name));

	phone = new char[strlen(p.phone) + 1];
	strncpy(phone, p.phone, strlen(p.phone));
}
//#endif

Person::~Person(void){
	delete []name;
	delete []phone;
}

void Person::showInfo(void){
	cout << "name : " << name << endl;
	cout << "phone : " << phone << endl;
}

int main(void){
	char name[32] = "나백수";
	char phone[32] = "010-8282-8282";

	Person p1(name, phone);
	Person p2(p1);

	p1.showInfo();
	p2.showInfo();

	return 0;
}








