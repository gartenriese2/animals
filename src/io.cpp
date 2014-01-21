#include "io.hpp"

#include <termios.h>
#include <unistd.h>

#include "areaconsole.hpp"

IO::IO() {
}

IO::~IO() {
}

IO & IO::instance() {
	static IO io;
	return io;
}

// void IO::emptyOutput() {

// 	while (!Console::textEmpty()) {
		
// 		Key key = getKey();
// 		if (key == Key::ENTER) {
// 			Console::advanceText();
// 			AreaConsole::print();
// 		}

// 	}

// }

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

	// emptyOutput();
	AreaConsole::addText("Please choose an attack with the arrow keys and press enter:");

	int choice = 0;
	// Console::setInputText(attacks[choice]->getName());
	AreaConsole::print();

	Key k;
	while ((k = getKey()) != Key::ENTER) {
		if (k == Key::DOWN) {
			choice = (choice + 1 == attacks.size() ? 0 : choice + 1);
		}
		if (k == Key::UP) {
			choice = (choice == 0 ? attacks.size() - 1 : choice - 1);
		}
		// AreaConsole::setInputText(attacks[choice]->getName());
		AreaConsole::print();
	}

	// Console::setInputText("");
	AreaConsole::advanceText();
	AreaConsole::print();

	return attacks[choice];

}

const std::string IO::chooseStarter() const {

	std::vector<std::string> v { "Firax", "Aquax" };

	int choice = 0;
	// Console::setInputText("I choose " + v[choice]);
	AreaConsole::print();
	
	Key k;
	while ((k = getKey()) != Key::ENTER) {
		if (k == Key::DOWN) {
			choice = (choice + 1 == v.size() ? 0 : choice + 1);
		}
		if (k == Key::UP) {
			choice = (choice == 0 ? v.size() - 1 : choice - 1);
		}
		// Console::setInputText("I choose " + v[choice]);
		AreaConsole::print();
	}

	// Console::setInputText("");
	AreaConsole::print();
	AreaConsole::addText("You chose " + v[choice] + ", the " + ((v[choice] == "Firax") ? "Fire" : "Water") + " animal!");
	AreaConsole::advanceText();
	AreaConsole::print();

	return v[choice];

}


Key IO::getKeyInstance() const {

	Key k = Key::NONE;
	
	int c = getch();
	switch (c) {
		case KEY_LEFT:
			k = Key::LEFT;
			break;
		case KEY_RIGHT:
			k = Key::RIGHT;
			break;
		case KEY_UP:
			k = Key::UP;
			break;
		case KEY_DOWN:
			k = Key::DOWN;
			break;
		case KEY_ENTER:
			k = Key::ENTER;
			break;
		case 'm':
			k = Key::MENU;
			break;
		default:
			break;
	};

	return k;

}

Key IO::getKey() {
	return instance().getKeyInstance();
}
