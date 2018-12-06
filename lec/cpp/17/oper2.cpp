#include <iostream>

using namespace std;

class Point{
private:
	int x, y;

public:
	Point(int x, int y);
	void showXY(void);
	Point operator+(Point& p);
};

Point::Point(int x, int y){
	this->x = x;
	this->y = y;
}

void Point::showXY(void){
	cout << x << ", " << y << endl;
}

Point Point::operator+(Point& p){
	Point tmp(x + p.x, y + p.y);
	return tmp;
}

int main(void){
	Point p1(1, 2);
	Point p2(3, 7);
	Point p3 = p1 + p2;
	p3.showXY();

	return 0;
}





