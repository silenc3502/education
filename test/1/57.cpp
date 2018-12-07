#include <iostream>

using namespace std;

class Char{
	float dam1;

public:
	Char(void){
		dam1 = 200;
	}
	Char(float d){
		dam1 = d;
	}
	virtual void skill1(void){
		cout << "s1 dam = " << dam1 * 2.3 << endl;
	}
	virtual void skill2(void){
		cout << "s1 dam = " << dam1 * 0.4 << endl;
		cout << " Knock-Back Accurance - 0.3s" << endl;
	}
};

class War : public Char{
	float s1_dam;

public:
	War(void) : Char(330){
		s1_dam = 570;
	}
	War(float coef){
		s1_dam = coef;
	}
	virtual void skill1(void){
		cout << "s1 dam = " << s1_dam * 3.3 << endl;
	}
	virtual void skill2(void){
		cout << "s2 dam = " << s1_dam * 1.4;
		cout << " Knock-Back Accurance - 1.0s" << endl;
	}
	virtual void skill3(void){
		cout << "s3 dam = " << s1_dam * 2.7 << endl;
	}
};

class Wiza : public Char{
	float s1_dam;

public:
	Wiza(void) : Char(330){
		s1_dam = 570;
	}
	Wiza(float coef){
		s1_dam = coef;
	}
	virtual void skill1(void){
		cout << "Hell Fire" << endl;
	}
	virtual void skill2(void){
		cout << "Blizzard" << endl;
	}
	virtual void skill3(void){
		cout << "Electric Field" << endl;
	}
};

class Thief : public Char{
	float s1_dam;

public:
	Thief(void) : Char(330){
		s1_dam = 570;
	}
	Thief(float coef){
		s1_dam = coef;
	}
	virtual void skill1(void){
		cout << "Back Step" << endl;
	}
	virtual void skill2(void){
		cout << "Double Step" << endl;
	}
	virtual void skill3(void){
		cout << "Tripple Step" << endl;
	}
};

class WarS2 : public War{
	float dam2;

public:
	WarS2(void) : War(700){
		dam2 = 1000;
	}
	virtual void skill1(void){
		cout << "s1 dam = " << dam2 * 4 << endl;
	}
	virtual void skill4(void){
		cout << "s4 dam = " << dam2 * 14.7 << endl;
	}
};

int main(void){
	War *Knight = new War();
	Knight->skill1();
	Knight->skill2();
	Knight->skill3();

	Wiza *W = new Wiza();
	W->skill1();
	W->skill2();
	W->skill3();

	Thief *t = new Thief();
	t->skill1();
	t->skill2();
	t->skill3();

	return 0;
}
