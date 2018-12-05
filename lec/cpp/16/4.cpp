#include <iostream>
#include <string.h>

using namespace std;

class Car
{
private:
	int speed;
	char color[32];

public:
	void setSpeed(int s);
	int getSpeed(void);
	void setColor(char *c);
	char *getColor(void);
};

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

	return 0;
}





