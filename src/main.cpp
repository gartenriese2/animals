#include <time.h>
#include <cstdlib>

#include "battle.hpp"

int main () {

	srand(time(NULL));

	Animal a1 = * Animal::getAnimal("Waterdevil");
	Animal a2 = * Animal::getAnimal("Duckweed");
	a1.setLevel(32);
	a1.heal();
	a2.setLevel(16);
	a2.heal();
	
	Battle b(a2,a1);
	b.startUservsAIRandom();
	
	return 0;
}
