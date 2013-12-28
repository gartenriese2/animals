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

void Tournament::startRandomBattles() {

	while(1) {

		std::cout << "-------------" << std::endl;
		std::cout << "NEXT BATTLE!" << std::endl;
		std::cout << "-------------" << std::endl;
		Animal own(Animal::getRandomAnimal());
		own.setLevel(rand() % 6 + 3);
		Animal foe(Animal::getRandomAnimal());
		foe.setLevel(rand() % 5 + 2);
		Battle b(own, foe);
		b.startUservsAIRandom();

	}

}

void Tournament::startWithFirestarter() {

	Animal own(Animal::getAnimal("Firestarter"));
	own.setLevel(5);

	while (true) {
		std::cout << "-------------" << std::endl;
		std::cout << "NEXT BATTLE!" << std::endl;
		std::cout << "-------------" << std::endl;
		Animal foe(Animal::getRandomAnimal());
		Battle b(own, foe);
		b.startUservsAIRandom();
		own.heal();
	}

}
