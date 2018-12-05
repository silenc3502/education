#include <iostream>

using namespace std;

class First{
	float first_skill_damage;

public:
	First(void){
		first_skill_damage = 270.3;
	}
	First(float coef){
		first_skill_damage = coef;
	}
	float get_fsd(void){
		return first_skill_damage;
	}
	virtual void skill1(void){
		cout << "skill 1 damage : " << first_skill_damage * 3.3 << endl;
	}
	virtual void skill2(void){
		cout << "skill 2 damage : " << first_skill_damage * 0.6;
		cout << " Knock-Back Accurance - 1.5s" << endl;
	}
};

class Second : public First{
	float second_skill_coef1;
	float second_skill_coef2;

public:
	Second(void) : First(372.7){
		second_skill_coef1 = 4.7;
		second_skill_coef2 = 2.4;
	}
	virtual void skill1(void){
		cout << "skill 1 damage : " << get_fsd() *
				(second_skill_coef1 + second_skill_coef2) << endl;
	}
	virtual void skill3(void){
		cout << "skill 3 damage : " << get_fsd() *
				(second_skill_coef1 * second_skill_coef2) / 4.0f;
		cout << " Area of Effect" << endl;
	}
};

int main(void){
	First *thief = new First();
	thief->skill1();
	thief->skill2();

	Second *rogue = new Second();
	rogue->skill1();
	rogue->skill2();
	rogue->skill3();

	return 0;
}
