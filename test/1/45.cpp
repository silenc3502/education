#include <iostream>

using namespace std;

class CompNum{
	int real;
	int imag;

public:
	CompNum(int real, int imag);
	CompNum operator+(CompNum& v);
	CompNum operator-(CompNum& v);
	void showInfo(void);
};

CompNum::CompNum(int real, int imag){
	this->real = real;
	this->imag = imag;
}

CompNum CompNum::operator+(CompNum& v){
	CompNum tmp(real + v.real, imag + v.imag);
	return tmp;
}

CompNum CompNum::operator-(CompNum& v){
	CompNum tmp(real - v.real, imag - v.imag);
	return tmp;
}

void CompNum::showInfo(void){
	cout << "real: " << real << ", imag: " << imag << "i" << endl;
}

int main(void){
	CompNum A(3, 3);
	A.showInfo();

	CompNum B(2, 2);
	B.showInfo();

	CompNum C = A + B;
	C.showInfo();

	C = A - B;
	C.showInfo();

	return 0;
}
