#include <iostream>
#include <string.h>

using namespace std;

class Academy
{
	char *name;
	char *phone;

public:
	Academy(char *n, char *p);
	void showInfo(void);
};

Academy::Academy(char *n, char *p)
{
	name = new char[strlen(n) + 1];
	strncpy(name, n, strlen(n));

	phone = new char[strlen(p) + 1];
	strncpy(phone, p, strlen(p));
}

void Academy::showInfo(void)
{
	cout << "name : " << name << endl;
	cout << "phone : " << phone << endl;
}

int main(void)
{
	Academy a("KOITT", "02-1544-4661");
	a.showInfo();

	return 0;
}





