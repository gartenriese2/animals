#include "io.hpp"

#include <termios.h>
#include <unistd.h>

#include "console.hpp"

IO::IO() {
}

IO::~IO() {
}

IO & IO::instance() {
	static IO io;
	return io;
}

void IO::emptyOutput() {

	while (!Console::textEmpty()) {
		
		Key key = getKey();
		if (key == Key::ENTER) {
			Console::advanceText();
			Console::printText();
		}

	}

}

void IO::printAttacks(const std::vector<std::shared_ptr<Attack>> & attacks) {

	std::cout << "\033[" << 4 + attacks.size() << "A";

	std::cout << "Possible Attacks: " << std::endl;

	for (const auto i : attacks) {
		std::cout << "---- " << i->getName() << std::endl;
	}

	std::cout << "\033[3B";

}

const std::shared_ptr<Attack> IO::chooseAttackWithArrowKeys(const std::vector<std::shared_ptr<Attack>> & attacks) {

	// printAttacks(attacks);

	emptyOutput();
	Console::addText("Please choose an attack with the arrow keys and press enter:");

	int choice = 0;
	Console::setInputText(attacks[choice]->getName());
	Console::printAllText();
	
	Key k;
	while ((k = getKey()) != Key::ENTER) {
		if (k == Key::DOWN) {
			choice = (choice + 1 == attacks.size() ? 0 : choice + 1);
		}
		if (k == Key::UP) {
			choice = (choice == 0 ? attacks.size() - 1 : choice - 1);
		}
		Console::setInputText(attacks[choice]->getName());
		Console::printInputText();
	}

	Console::setInputText("");
	Console::advanceText();
	Console::printAllText();

	return attacks[choice];

}

const std::string IO::chooseStarter() const {

	std::vector<std::string> v { "Firax", "Aquax" };

	int choice = 0;
	Console::setInputText("I choose " + v[choice]);
	Console::printInputText();
	
	Key k;
	while ((k = getKey()) != Key::ENTER) {
		if (k == Key::DOWN) {
			choice = (choice + 1 == v.size() ? 0 : choice + 1);
		}
		if (k == Key::UP) {
			choice = (choice == 0 ? v.size() - 1 : choice - 1);
		}
		Console::setInputText("I choose " + v[choice]);
		Console::printInputText();
	}

	Console::setInputText("");
	Console::printInputText();
	Console::addText("You chose " + v[choice] + ", the " + ((v[choice] == "Firax") ? "Fire" : "Water") + " animal!");
	Console::advanceText();
	Console::printText();

	return v[choice];

}


Key IO::getKeyInstance() const {
	
	static struct termios oldt, newt;
	tcgetattr( STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON);
	newt.c_lflag &= ~ECHO;
	tcsetattr( STDIN_FILENO, TCSANOW, &newt);

	Key k = Key::NONE;
	int c1 = getchar();
	if (c1 == 27) {
		int c2 = getchar();
		if (c2 == 91) {
			int c3 = getchar();
			if (c3 == 65) {
				k = Key::UP;
			} else
			if (c3 == 66) {
				k = Key::DOWN;
			} else
			if (c3 == 67) {
				k = Key::RIGHT;
			} else
			if (c3 == 68) {
				k = Key::LEFT;
			}
		}
	} else if (c1 == 10) {
		k = Key::ENTER;
	} else if (c1 == 'm') {
		k = Key::MENU;
	}

	tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
	return k;

}

Key IO::getKey() {
	return instance().getKeyInstance();
}
