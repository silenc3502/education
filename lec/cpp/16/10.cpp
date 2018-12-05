#include <iostream>

using namespace std;

class Point
{
private:
	int x;
	int y;

public:
	Point(void);
	Point(int x, int y);
	int getX(void);
	int getY(void);
	void setX(int x);
	void setY(int y);
	void showInfo(void);
};

Point::Point(void)
{
	cout << "Point(void) Call" << endl;
}

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

int Point::getX(void)
{
	return x;
}

int Point::getY(void)
{
	return y;
}

void Point::setX(int x)
{
	this->x = x;
}

void Point::setY(int y)
{
	this->y = y;
}

void Point::showInfo(void)
{
	cout << "x = " << x << ", y = " << y << endl;
}

int main(void)
{
	Point arr[5];

	for(int i = 0; i < 5; i++)
	{
		arr[i].setX((i + 1) * 2);
		arr[i].setY((i + 1) * 3);
	}

	for(int j = 0; j < 5; j++)
		arr[j].showInfo();

	return 0;
}
