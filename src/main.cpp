#include <time.h>
#include <cstdlib>
#include <random>

#include "tournament.hpp"

std::mt19937 generator;

int main () {

	std::random_device rd;
	std::mt19937 mt(rd());
	generator = mt;

	Animal::printAnimalsSortByAllStats(50);
	std::cout << std::endl;
	Animal::printAnimalsSortByHealth(50);
	std::cout << std::endl;
	Animal::printAnimalsSortByAttack(50);
	std::cout << std::endl;
	Animal::printAnimalsSortByDefense(50);
	std::cout << std::endl;
	Animal::printAnimalsSortBySpeed(50);
	
	Tournament t;
	t.startWithFirestarter();
	// t.startRandomBattles(40,50);
	
	return 0;

}
