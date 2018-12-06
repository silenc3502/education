#include <iostream>
#include <string.h>

using namespace std;

class GHL{
private:
	char coporate[32];
	int stock;
	int money;

public:
	GHL(char *c, int s, int m);
	char *getCoporate(void);
	int getStock(void);
	int getMoney(void);
};

GHL::GHL(char *c, int s, int m){
	strcpy(coporate, c);
	stock = s;
	money = m;
}

char *GHL::getCoporate(void){
	return coporate;
}

int GHL::getStock(void){
	return stock;
}

int GHL::getMoney(void){
	return money;
}

class JYL : public GHL{
	char nick[32];

public:
	JYL(char *n, char *c, int s, int m);
	char *getNick(void);
	void showInfo(void);
};

JYL::JYL(char *n, char *c, int s, int m) : GHL(c, s, m){
	strcpy(nick, n);
}

char *JYL::getNick(void){
	return nick;
}

void JYL::showInfo(void){
	cout << "nickname : " << getNick() << endl;
	cout << "coporate : " << getCoporate() << endl;
	cout << "stock : " << getStock() << endl;
	cout << "money : " << getMoney() << endl;
}

int main(void){
	char nick[32] = "다이아 수저";
	char copor[32] = "삼성";

	JYL Jaeyong(nick, copor, 70000000, 2100000000);
	Jaeyong.showInfo();

	return 0;
}
