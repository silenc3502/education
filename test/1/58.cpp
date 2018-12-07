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

class Mage : public Wiza{
	float dam2;

public:
	Mage(void) : Wiza(210){
		dam2 = 330;
	}
	virtual void skill1(void){
		cout << "Apocalipse" << endl;
	}
	virtual void skill4(void){
		cout << "Meteor Strike" << endl;
	}
};

class Rogue : public Thief{
	float dam2;

public:
	Rogue(void) : Thief(210){
		dam2 = 330;
	}
	virtual void skill1(void){
		cout << "Quad Step" << endl;
	}
	virtual void skill4(void){
		cout << "Mangle Felon" << endl;
	}
};

int main(void){
	cout << "Knight" << endl;
	War *Knight = new War();
	Knight->skill1();
	Knight->skill2();
	Knight->skill3();

	cout << "Wizard" << endl;
	Wiza *W = new Wiza();
	W->skill1();
	W->skill2();
	W->skill3();

	cout << "Thief" << endl;
	Thief *t = new Thief();
	t->skill1();
	t->skill2();
	t->skill3();

	cout << "Holy Knight" << endl;
	WarS2 *HK = new WarS2();
	HK->skill1();
	HK->skill2();
	HK->skill3();
	HK->skill4();

	cout << "Flame Mage" << endl;
	Mage *fm = new Mage();
	fm->skill1();
	fm->skill2();
	fm->skill3();
	fm->skill4();

	cout << "Assasin" << endl;
	Rogue *a = new Rogue();
	a->skill1();
	a->skill2();
	a->skill3();
	a->skill4();

	return 0;
}
