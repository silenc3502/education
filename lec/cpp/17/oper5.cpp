#include <iostream>

using namespace std;

class Point{
private:
	int x, y;

public:
	Point(int x, int y);
	void showXY(void);
	Point operator+(int val);
	friend Point operator+(int val, Point& p);
};

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Point::showXY(void){
	cout << x << ", " << y << endl;
}

Point Point::operator+(int val){
	Point tmp(x + val, y + val);
	return tmp;
}

Point operator+(int val, Point& p){
	return p + val;
}

int main(void){
	Point p1(3, 7);
	Point p2 = p1 + 3;
	p2.showXY();

	Point p3 = 7 + p2;
	p3.showXY();

	return 0;
}




