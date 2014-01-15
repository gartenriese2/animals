#include <time.h>
#include <cstdlib>
#include <random>

#include <termios.h>
#include <unistd.h>

#include "game.hpp"

#include "console.hpp"

std::mt19937 generator;

int main () {

	std::random_device rd;
	std::mt19937 mt(rd());
	generator = mt;

	// Animal::printAnimalsSortByAllStats(50);
	// std::cout << std::endl;
	// Animal::printAnimalsSortByHealth(50);
	// std::cout << std::endl;
	// Animal::printAnimalsSortByAttack(50);
	// std::cout << std::endl;
	// Animal::printAnimalsSortByDefense(50);
	// std::cout << std::endl;
	// Animal::printAnimalsSortBySpeed(50);
	
	// Tournament t;
	// t.startWithWaterstarter();
	// t.startRandomBattles(40,50);

	Game game;

	// std::cout << "\033[t";
	// std::string str;
	// std::cin >> str;
	// std::cout << str << std::endl;

	return 0;

}
