#include <iostream>
#include <string>

#include "fight.hpp"

void compare(Type type1, Type type2) {

	std::cout << type1 << " against " << type2 << ": " << type1.getEffectStringAgainst(type2) 
			<< " (" << type1.getEffectValueAgainst(type2) << ")" << std::endl;
	std::cout << type2 << " against " << type1 << ": " << type2.getEffectStringAgainst(type1) 
			<< " (" << type2.getEffectValueAgainst(type1) << ")" << std::endl;

}

int main () {

	Type t1(BaseType::Plant, BaseType::Water);
	Type t2(BaseType::Air, BaseType::Magic);
	Type t3(BaseType::Ghost, BaseType::Psycho);
	Type t4(BaseType::Technology, BaseType::Electro);
	Type t5(BaseType::Magic, BaseType::Ghost);
	Type t6(BaseType::Fire, BaseType::Water);
	compare(t1,t2);
	compare(t3,t2);
    compare(t4,t1);
    compare(t3,t1);
    compare(t1,t5);
    compare(t2,t5);
    compare(t3,t5);
    compare(t4,t5);
    compare(t6,t5);
    compare(t6,t4);
    compare(t6,t3);
    compare(t6,t2);
    compare(t6,t1);

    Attack a(Type(BaseType::Normal), 50);
    std::vector<Attack> moves = {a};
    Animal a1(t6, 120, moves);
    Animal a2(t1, 80, moves);
    Fight f(a1,a2);
    f.printStatus();
    f.oneAttacks(a);
    f.twoAttacks(a);
    f.printStatus();

    return 0;
}
