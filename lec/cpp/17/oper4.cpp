#include <iostream>

using namespace std;

class Point{
private:
	int x, y;

public:
	Point(int x, int y);
	void showXY(void);
	Point& operator++(void);
	Point operator++(int);
};

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Point::showXY(void){
	cout << x << ", " << y << endl;
}

Point& Point::operator++(void){
	x++;
	y++;
	return *this;
}

Point Point::operator++(int){
	Point tmp(x, y);
	x++;
	y++;

	return tmp;
}

int main(void){
	Point p1(3, 7);
	(p1++).showXY();
	p1.showXY();

	Point p2(33, 77);
	(++p2).showXY();
	p2.showXY();

	return 0;
}
