#include <iostream>
#include <string.h>

using namespace std;

class Person{
private:
	int age;
	char name[20];

public:
	Person(int a, char *n);
	int getAge(void);
	char *getName(void);
};

Person::Person(int a, char *n){
	age = a;
	strcpy(name, n);
}

char *Person::getName(void){
	return name;
}

int Person::getAge(void){
	return age;
}

class Student : public Person{
	char major[20];

public:
	Student(int a, char *n, char *m);
	char *getMajor(void);
	void showInfo(void);
};

Student::Student(int a, char *n, char *m) : Person(a, n){
	strcpy(major, m);
}

char *Student::getMajor(void)
{
	return major;
}

void Student::showInfo(void){
	cout << "name : " << getName() << endl;
	cout << "age : " << getAge() << endl;
	cout << "major : " << getMajor() << endl;
}

int main(void){
	Student Kim(24, "Kim Su Hyun", "Computer Science");
	Kim.showInfo();

	return 0;
}
