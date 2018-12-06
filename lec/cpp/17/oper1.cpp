#include <iostream>

using namespace std;

class Point{
private:
	int x, y;

public:
	Point(int x, int y);
	void showXY(void);
	void operator+(int val);
};

Point::Point(int x, int y){
	this->x = x;
	this->y = y;
}

void Point::showXY(void){
	cout << x << ", " << y << endl;
}

void Point::operator+(int val){
	x += val;
	y += val;
}

int main(void){
	Point p(3, 4);
	p.showXY();

	p.operator+(10);	// p + 10
	p.showXY();

	return 0;
}




