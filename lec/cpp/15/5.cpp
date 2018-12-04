#include <iostream>
#include <string.h>

using namespace std;

class Person
{
public:
	int age;
	char name[32];
	char job[32];

	void setAge(int);
	int getAge(void);
	void setName(char *);
	char *getName(void);
	void setJob(char *);
	char *getJob(void);
};

void Person::setAge(int a)
{
	age = a;
}

int Person::getAge(void)
{
	return age;
}

void Person::setName(char *n)
{
	strcpy(name, n);
}

char *Person::getName(void)
{
	return name;
}

void Person::setJob(char *j)
{
	strcpy(job, j);
}

char *Person::getJob(void)
{
	return job;
}

int main(void)
{
	Person p = Person();

	p.setAge(41);
	cout << "age = " << p.getAge() << endl;
	p.setName("나백수");
	cout << "name = " << p.getName() << endl;
	p.setJob("백수");
	cout << "job = " << p.getJob() << endl;

	return 0;
}
