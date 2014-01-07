#include <time.h>
#include <cstdlib>
#include <random>

#include <termios.h>
#include <unistd.h>

#include "tournament.hpp"
#include "game.hpp"

std::mt19937 generator;

class Test {

	public:

		// Test(const Type &, int, int odmg = 0, float p = 1.f,
		// 	float fam = 1.f, float fdm = 1.f, float fsm = 1.f,
		// 	float oam = 1.f, float odm = 1.f, float osm = 1.f,
		// 	float ohm = 0.f) {
		// 	std::cout << "default parameter constructor!" << std::endl;
		// }

		// Test(const Type &, int, float) {
		// 	std::cout << "normal constructor!" << std::endl;
		// }

		Test(std::pair<char const *, int>) {
			std::cout << "normal constructor 2!" << std::endl;
		}

		template<typename ... Tn>
		Test(Tn ... args) {
			std::cout << "template constructor!" << std::endl;
			// handleTemplateArgs(args ...);
		}

		// template<typename T>
		// void handleTemplateArgs(T arg) {
		// 	handleArg(arg);
		// }
		// template<typename T1, typename ... Tn>
		// void handleTemplateArgs(T1 arg, Tn ... args) {
		// 	handleTemplateArgs(arg);
		// 	handleTemplateArgs(args ...);
		// }

		// void handleArg(int i) {
		// 	std::cout << "int " << i << std::endl;
		// }
		// void handleArg(float f) {
		// 	std::cout << "float " << f << std::endl;
		// }
		// void handleArg(const Type & t) {
		// 	std::cout << "Type" << std::endl;
		// }
		// void handleArg(std::pair<char *,int> p) {
		// 	std::cout << "pair" << std::endl;
		// }
		// void handleArg(char * c) {
		// 	std::cout << "char" << c << std::endl;
		// }

};

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
	
	Tournament t;
	// t.startWithWaterstarter();
	// t.startRandomBattles(40,50);

	Game game;
	
	// Test t1(6, 2.3f);
	// Test t2("Hallo Welt");
	// Test t3(22,10,1.f);
	// Test t4(Type(BaseType::Fire), 25, 0.95f);
	// Test t5(Type(BaseType::Fire), 50, 0, 0.95f);
	// Test t6{{"Test", 42}};
	
	return 0;

}
