#include "io.hpp"

#include <termios.h>
#include <unistd.h>

IO::IO() {
}

IO::~IO() {
}

void IO::printAttacks(const std::vector<std::shared_ptr<Attack>> & attacks) {

	std::cout << "Possible Attacks: " << std::endl;

	for (const auto i : attacks) {
		std::cout << "---- " << i->getName() << std::endl;
	}

}

const std::shared_ptr<Attack> IO::chooseAttack(const std::vector<std::shared_ptr<Attack>> & attacks) {

	printAttacks(attacks);

	std::cout << "Please enter the attack you choose: ";
	std::string str;
	std::getline(std::cin, str);

	for (const auto i : attacks) {
		if (i->getName() == str) return i;
	}

	return std::shared_ptr<Attack>();

}

const std::shared_ptr<Attack> IO::chooseAttackWithArrowKeys(const std::vector<std::shared_ptr<Attack>> & attacks) {

	printAttacks(attacks);

	int choice = 0;
	std::cout << "Please choose an attack with the arrow keys and press enter: " << attacks[choice]->getName();
	
	ArrowKey k;
	while ((k = getArrowKey()) != ArrowKey::ENTER) {
		if (k == ArrowKey::DOWN) {
			choice = (choice + 1 == attacks.size() ? 0 : choice + 1);
		}
		if (k == ArrowKey::UP) {
			choice = (choice == 0 ? attacks.size() - 1 : choice - 1);
		}
		std::cout << "\r\033[K" << "Please choose an attack with the arrow keys and press enter: " << attacks[choice]->getName();
	}

	std::cout << std::endl;
	return attacks[choice];

}

ArrowKey IO::getArrowKey() {
	
	static struct termios oldt, newt;
	tcgetattr( STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON);
	newt.c_lflag &= ~ECHO;
	tcsetattr( STDIN_FILENO, TCSANOW, &newt);

	ArrowKey k = ArrowKey::NONE;
	int c1 = getchar();
	if (c1 == 27) {
		int c2 = getchar();
		if (c2 == 91) {
			int c3 = getchar();
			if (c3 == 65) {
				k = ArrowKey::UP;
			} else
			if (c3 == 66) {
				k = ArrowKey::DOWN;
			} else
			if (c3 == 67) {
				k = ArrowKey::RIGHT;
			} else
			if (c3 == 68) {
				k = ArrowKey::LEFT;
			}
		}
	} else
	if (c1 == 10) {
		k = ArrowKey::ENTER;
	}

	tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
	return k;

}
