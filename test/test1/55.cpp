#include <iostream>
#include <math.h>

using namespace std;

class Vector{
	int x;
	int y;
	int z;

public:
	Vector(void) {};
	Vector(int x, int y, int z);
	void setVector(Vector& v);
	Vector operator+(Vector& v);
	Vector operator-(Vector& v);
	Vector operator*(int scale);
	friend Vector operator*(int scale, Vector& v);
	void showInfo(void);
	int inner(Vector& v);
};

Vector::Vector(int x, int y, int z){
	this->x = x;
	this->y = y;
	this->z = z;
}

void Vector::setVector(Vector& v){
	x = v.x;
	y = v.y;
	z = v.z;
}

Vector Vector::operator+(Vector& v){
	Vector tmp(x + v.x, y + v.y, z + v.z);
	return tmp;
}

Vector Vector::operator-(Vector& v){
	Vector tmp(x - v.x, y - v.y, z - v.z);
	return tmp;
}

Vector Vector::operator*(int scale){
	Vector tmp(x * scale, y * scale, z * scale);
	return tmp;
}

Vector operator*(int scale, Vector& v){
	return v * scale;
}

void Vector::showInfo(void){
	cout << "x: " << x << ", y: " << y << "z: " << z << endl;
}

int Vector::inner(Vector& v){
	return x * v.x + y * v.y + z * v.z;
}

class Triangle{
	int height;
	int base;

	float side1;
	float side2;
	float angle;

	float area;

	Vector v1;
	Vector v2;
	Vector v3;

public:
	Triangle(Vector, Vector, Vector);
	Triangle(float, float, float);
	Triangle(int, int);
	void calcAreaHB(void);
	float getArea(void);
	void calcAreaS2A(void);
	void setVector(Vector&);
	void showInfo(void);
	//friend float deg2rad(float);
};

float deg2rad(float deg){
	return deg * 180 / M_PI;
}

Triangle::Triangle(Vector a, Vector b, Vector c){
	v1.setVector(a);
	v2.setVector(b);
	v3.setVector(c);
}

Triangle::Triangle(float s1, float s2, float angle){
	side1 = s1;
	side2 = s2;
	this->angle = deg2rad(angle);
}

Triangle::Triangle(int h, int b){
	height = h;
	base = b;
}

void Triangle::calcAreaHB(void){
	area = (float)(height * base) / 2.0f;
}

float Triangle::getArea(void){
	return area;
}

void Triangle::calcAreaS2A(void){
	area = 0.5 * (side1 * side2) * sin(angle);
}

void Triangle::showInfo(void){
	v1.showInfo();
	v2.showInfo();
	v3.showInfo();
}

int main(void){
	Triangle t1(Vector(2, 1, 0), Vector(4, 3, 0), Vector(3, 5, 0));
	t1.showInfo();

	Triangle t2(3, 5);
	t2.calcAreaHB();
	cout << "Area = " << t2.getArea() << endl;

	Triangle t3(4, 3, 60);
	t3.calcAreaS2A();
	cout << "Area = " << t3.getArea() << endl;

	return 0;
}
