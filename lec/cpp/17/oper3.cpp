#include <iostream>

using namespace std;

class Point{
private:
	int x, y;

public:
	Point(int x, int y);
	void showXY(void);
	Point& operator++(void);
	friend Point& operator--(Point& p);
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

Point& operator--(Point& p){
	p.x--;
	p.y--;
	return p;
}

int main(void){
	Point p(3, 7);
	++p;
	p.showXY();

	--p;
	p.showXY();

	++(++p);
	p.showXY();

	--(--p);
	p.showXY();

	return 0;
}
