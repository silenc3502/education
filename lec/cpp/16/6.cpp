#include <iostream>
#include <string.h>

using namespace std;

class Person
{
private:
	int age;
	char name[32];
	char job[32];

public:
	Person(int a, char *n, char *j);
	void setAge(int);
	int getAge(void);
	void setName(char *);
	char *getName(void);
	void setJob(char *);
	char *getJob(void);
};

Person::Person(int a, char *n, char *j)
{
	cout << "I'm Person" << endl;
	age = a;
	strcpy(name, n);
	strcpy(job, j);
}

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
	char data[32] = "나바보";
	Person p = Person(41, "어디가", "집가요");

	//p.setAge(41);
	cout << "age = " << p.getAge() << endl;
	//p.setName("나백수");
	cout << "name = " << p.getName() << endl;
	//p.setJob("백수");
	cout << "job = " << p.getJob() << endl;

#if 0
	p.age = 23;
	strcpy(p.name, data);
	strcpy(p.job, "바보");

	cout << "age = " << p.getAge() << endl;
	cout << "name = " << p.getName() << endl;
	cout << "job = " << p.getJob() << endl;
#endif

	return 0;
}






