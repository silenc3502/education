#include <iostream>
#include <string.h>

using namespace std;

class Car
{
private:
	int speed;
	char color[32];

public:
	Car(void);
	Car(int speed, char *c);
	void setSpeed(int s);
	int getSpeed(void);
	void setColor(char *c);
	char *getColor(void);
};

Car::Car(void)
{
	cout << "I'm Car Default Constructor!!!" << endl;
}

Car::Car(int s, char *c)
{
	speed = s;
	strncpy(color, c, strlen(c));
	cout << "I'm Car Default Constructor too" << endl;
}

void Car::setSpeed(int s)
{
	speed = s;
}

int Car::getSpeed(void)
{
	return speed;
}

void Car::setColor(char *c)
{
	strcpy(color, c);
}

char *Car::getColor(void)
{
	return color;
}

int main(void)
{
	Car c = Car();

	c.setSpeed(180);
	cout << "speed = " << c.getSpeed() << endl;

	c.setColor("파랑");
	cout << "색상 = " << c.getColor() << endl;

	char color[32] = "빨강";
	Car c2 = Car(300, color);
	cout << "speed = " << c2.getSpeed() << endl;
	cout << "색상 = " << c2.getColor() << endl;

	return 0;
}





