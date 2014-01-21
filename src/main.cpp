#include <time.h>
#include <cstdlib>
#include <random>

#include <termios.h>
#include <unistd.h>

#include "game.hpp"

std::mt19937 generator;

int main () {

	std::random_device rd;
	std::mt19937 mt(rd());
	generator = mt;

	//static struct termios t;
	//tcgetattr( STDIN_FILENO, &t);
	//t.c_lflag &= ECHO;
	//tcsetattr( STDIN_FILENO, TCSANOW, &t);

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

	
// setlocale(LC_ALL,"");
// initscr();
// addstr("\u01C1");
// getch();
// endwin();
	
	Game game;
	
	// initscr();
	// printw("Hallo");
	// refresh();
	// getch();
	// endwin();

	return 0;

}
