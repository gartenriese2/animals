#include "io.hpp"

#include <termios.h>
#include <unistd.h>

#include "areaconsole.hpp"
#include "battleconsole.hpp"

IO::IO() {
}

IO::~IO() {
}

IO & IO::instance() {
	static IO io;
	return io;
}

const std::shared_ptr<Attack> IO::chooseAttack(const std::vector<std::shared_ptr<Attack>> & attacks) {

	BattleConsole::addText("Please choose an attack with the arrow keys and press enter:");
	BattleConsole::print();

	std::vector<std::string> vec;
	for (const auto & i : attacks) {
		if (vec.size() == 4) break;
		vec.emplace_back(i->getName());
	}

	BattleConsole::printAttacks(vec);

	unsigned int choice = 0;
	Key k;
	while ((k = getKey()) != Key::ENTER) {
		if (k == Key::DOWN && choice < 2 && vec.size() > choice + 2) choice += 2;
		if (k == Key::UP && choice > 1) choice -= 2;
		if (k == Key::RIGHT && choice % 2 == 0 && vec.size() > choice + 1) ++choice;
		if (k == Key::LEFT && choice % 2 == 1) --choice;

		BattleConsole::printAttacks(vec, choice);
	}

	BattleConsole::advanceText();
	BattleConsole::print();
	BattleConsole::clearAttacks();

	return attacks[choice];

}

const std::string IO::chooseStarter() const {

	std::vector<std::string> starter { "Firax", "Aquax" };

	std::string question("Which animal do you choose as your starter animal?");
	std::vector<std::string> questionVec = Console::splitString(question);

	for (unsigned int i = 0; i < questionVec.size(); ++i) {
		
		Console::moveCursorTo(Console::getHeight() / 2 - 3 + i, (Console::getWidth() - questionVec[i].size()) / 2);
		waddstr(Console::win(), questionVec[i].c_str());

	}

	Console::moveCursorDown(2);
	Console::moveCursorToCol(Console::getWidth() / 2 - starter[0].size() - 5);
	unsigned int col0 = getcurx(Console::win()) - 1;
	waddstr(Console::win(), starter[0].c_str());
	Console::moveCursorRight(10);
	unsigned int col1 = getcurx(Console::win()) - 1;
	waddstr(Console::win(), starter[1].c_str());

	Console::moveCursorToCol(col0);
	wprintw(Console::win(), ">");

	wrefresh(Console::win());

	int choice = 0;
	
	Key k;
	while ((k = getKey()) != Key::ENTER) {
		
		if (k == Key::RIGHT && choice != 1) {
			choice = 1;
			Console::moveCursorToCol(col1);
			wprintw(Console::win(), ">");
			Console::moveCursorToCol(col0);
			wprintw(Console::win(), " ");
			wrefresh(Console::win());
		}
		if (k == Key::LEFT && choice != 0) {
			choice = 0;
			Console::moveCursorToCol(col0);
			wprintw(Console::win(), ">");
			Console::moveCursorToCol(col1);
			wprintw(Console::win(), " ");
			wrefresh(Console::win());
		}
		
		
	}

	return starter[choice];

}


Key IO::getKeyInstance() const {

	Key k = Key::NONE;

	int c = wgetch(Console::win());
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
		case '\n':
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
