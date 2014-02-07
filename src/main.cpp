#include <time.h>
#include <random>

#include "game.hpp"

std::mt19937 generator;

int main () {

	std::random_device rd;
	std::mt19937 mt(rd());
	generator = mt;
	
	Game game;
	
	return 0;

}
