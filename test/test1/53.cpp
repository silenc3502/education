#include <iostream>

using namespace std;

class Vector{
	int x;
	int y;

public:
	Vector(void) {};
	Vector(int x, int y);
	void setVector(Vector& v);
	Vector operator+(Vector& v);
	Vector operator-(Vector& v);
	Vector operator*(int scale);
	friend Vector operator*(int scale, Vector& v);
	void showInfo(void);
	int inner(Vector& v);
};

Vector::Vector(int x, int y){
	this->x = x;
	this->y = y;
}

void Vector::setVector(Vector& v){
	x = v.x;
	y = v.y;
}

Vector Vector::operator+(Vector& v){
	Vector tmp(x + v.x, y + v.y);
	return tmp;
}

Vector Vector::operator-(Vector& v){
	Vector tmp(x - v.x, y - v.y);
	return tmp;
}

Vector Vector::operator*(int scale){
	Vector tmp(x * scale, y * scale);
	return tmp;
}

Vector operator*(int scale, Vector& v){
	return v * scale;
}

void Vector::showInfo(void){
	cout << "x: " << x << ", y: " << y << endl;
}

int Vector::inner(Vector& v){
	return x * v.x + y * v.y;
}

class Triangle{
	Vector v1;
	Vector v2;
	Vector v3;

public:
	Triangle(Vector, Vector, Vector);
	void setVector(Vector&);
	void showInfo(void);
};

Triangle::Triangle(Vector a, Vector b, Vector c){
	v1.setVector(a);
	v2.setVector(b);
	v3.setVector(c);
}

void Triangle::showInfo(void){
	v1.showInfo();
	v2.showInfo();
	v3.showInfo();
}

int main(void){
	Triangle t(Vector(2, 1), Vector(4, 3), Vector(3, 5));
	t.showInfo();

	return 0;
}
