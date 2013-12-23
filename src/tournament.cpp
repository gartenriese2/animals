#include "tournament.hpp"

Tournament::Tournament() {

}

Tournament::~Tournament() {

}

void Tournament::startSingleBattle(Animal & a1, Animal & a2) {

	Battle b(a1, a2);
	b.startUservsAIRandom();

}

void Tournament::startSingleRandomBattle(Animal & a1) {

	Animal a2(Animal::getRandomAnimal());
	Battle b(a1, a2);
	b.startUservsAIRandom();

}

void Tournament::startSingleRandomBattle() {

	Animal a1(Animal::getRandomAnimal());
	Animal a2(Animal::getRandomAnimal());
	Battle b(a1, a2);
	b.startUservsAIRandom();

}

void Tournament::startKOBattles() {

	Animal own(Animal::getRandomAnimal());
	unsigned int victories = 0;
	while (own.getActualHealth() > 0) {
		std::cout << "-------------" << std::endl;
		std::cout << "NEXT BATTLE!" << std::endl;
		std::cout << "-------------" << std::endl;
		Animal foe(Animal::getRandomAnimal());
		Battle b(own, foe);
		b.startUservsAIRandom();
		if (own.getActualHealth() > 0) {
			++victories;
		}
	}

	std::cout << "You won " << victories << " times!" << std::endl;

}
