#include <iostream>
#include <string>
#include <time.h>

#include "battle.hpp"

void compare(Type type1, Type type2) {

	std::cout << type1 << " against " << type2 << ": " << type1.getEffectStringAgainst(type2) 
			<< " (" << type1.getEffectValueAgainst(type2) << ")" << std::endl;
	std::cout << type2 << " against " << type1 << ": " << type2.getEffectStringAgainst(type1) 
			<< " (" << type2.getEffectValueAgainst(type1) << ")" << std::endl;

}

int main () {

	srand(time(NULL));

	Type t1(BaseType::Plant, BaseType::Water);
	Type t2(BaseType::Air, BaseType::Magic);
	Type t3(BaseType::Ghost, BaseType::Psycho);
	Type t4(BaseType::Technology, BaseType::Electro);
	Type t5(BaseType::Magic, BaseType::Ghost);
	Type t6(BaseType::Fire, BaseType::Water);
	// compare(t1,t2);
	// compare(t3,t2);
	// compare(t4,t1);
	// compare(t3,t1);
	// compare(t1,t5);
	// compare(t2,t5);
	// compare(t3,t5);
	// compare(t4,t5);
	// compare(t6,t5);
	// compare(t6,t4);
	// compare(t6,t3);
	// compare(t6,t2);
	// compare(t6,t1);

	Attack atk1("Tackle", Type(BaseType::Normal), 30);
	Attack atk2("Water Blast", Type(BaseType::Water), 50);
	Attack atk3("Fire Blast", Type(BaseType::Fire), 50);
	Attack atk4("Twine", Type(BaseType::Plant), 40);
	Stats s1(120,80,100, 2.4f);
	Stats s2(80,100,100, 1.5f);
	Animal a1("Waterdevil", t6, s1, {atk1, atk2, atk3});
	Animal a2("Duckweed", t1, s2, {atk1, atk2, atk4});
	a1.setLevel(47);
	a1.heal();
	a2.setLevel(42);
	a2.heal();
	
	Battle b(a1,a2);
	b.startAIvsAIRandom(true);
	
	return 0;
}
