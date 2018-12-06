#include <iostream>

using namespace std;

class Vector{
	int x;
	int y;
	int z;

public:
	Vector(int x, int y, int z);
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
	cout << "x: " << x << ", y: " << y << ", z: " << z << endl;
}

int Vector::inner(Vector& v){
	return x * v.x + y * v.y + z * v.z;
}

int main(void){
	Vector A(7, 4, 3);
	A.showInfo();

	Vector B(2, 4, 6);
	B.showInfo();

	Vector C = A + B;
	C.showInfo();

	C = A - B;
	C.showInfo();

	C = A * 3;
	C.showInfo();

	C = 3 * A;
	C.showInfo();

	int inner_res = A.inner(B);
	cout << "내적 결과 = " << inner_res << endl;

	return 0;
}
