#include "battleconsole.hpp"

#include <algorithm>

#include "io.hpp"

//
// STATIC
//

void BattleConsole::print() {

	Console::clear();

	instance().printBorders();
	instance().printText();

	Console::refresh();

}

void BattleConsole::printAttacks(const std::vector<std::string> & vec, unsigned int highlight) {

	Console::clear();

	instance().printBorders();
	instance().printText();

	init_pair(1, COLOR_GREEN, -1);

	instance().moveCursorToTopOfTextOutput();
	Console::moveCursorDown(2);
	Console::moveCursorToCol(Console::getWidth() / 3 - vec[0].size() / 2);
	if (highlight == 0) wattron(Console::win(), COLOR_PAIR(1));
	wprintw(Console::win(), vec[0].c_str());
	wattroff(Console::win(), COLOR_PAIR(1));

	if (vec.size() > 1) {
		Console::moveCursorToCol(Console::getWidth() * 2 / 3 - vec[1].size() / 2);
		if (highlight == 1) wattron(Console::win(), COLOR_PAIR(1));
		wprintw(Console::win(), vec[1].c_str());
		wattroff(Console::win(), COLOR_PAIR(1));
	}

	if (vec.size() > 2) {
		Console::moveCursorDown(2);
		Console::moveCursorToCol(Console::getWidth() / 3 - vec[2].size() / 2);
		if (highlight == 2) wattron(Console::win(), COLOR_PAIR(1));
		wprintw(Console::win(), vec[2].c_str());
		wattroff(Console::win(), COLOR_PAIR(1));
	}

	if (vec.size() > 3) {
		Console::moveCursorToCol(Console::getWidth() * 2 / 3 - vec[3].size() / 2);
		if (highlight == 3) wattron(Console::win(), COLOR_PAIR(1));
		wprintw(Console::win(), vec[3].c_str());
		wattroff(Console::win(), COLOR_PAIR(1));
	}
	
	Console::refresh();

}

void BattleConsole::addText(const std::string & str) {
	
	std::vector<std::string> vec = Console::splitString(str, instance().m_textWidth);

	for (const auto i : vec) {
		instance().m_text.emplace_back(i);
	}

}

void BattleConsole::advanceText() {
	if (instance().m_text.size() > 0) {
		instance().m_text.pop_front();
	}
}

void BattleConsole::emptyText() {

	while (!textEmpty()) {
		
		Key key = IO::getKey();

		if (key == Key::ENTER) {
			advanceText();
			print();
		}

	}

}

//
// MEMBER
//

BattleConsole::BattleConsole() {

	m_textHeight = 1;
	m_textWidth = Console::getWidth() - 10;

}

void BattleConsole::printBorders() const {

	Console::printBorders();
	moveCursorToLowerBorder();

	waddstr(Console::win(), "\u251C");
	for (unsigned int i = 0; i < Console::getWidth() - 2; ++i) {
		waddstr(Console::win(), "\u2500");
	}
	waddstr(Console::win(), "\u2524");

}

void BattleConsole::printText() const {

	for (unsigned int i = 0; i < m_textHeight; ++i) {
		
		moveCursorToTopOfTextOutput();
		Console::moveCursorDown(i);
		Console::moveCursorRight();

		Console::clearLine();

		if (m_text.size() > i) {
			Console::moveCursorRight((Console::getWidth() - 2 - m_text[i].size()) / 2);
			wprintw(Console::win(),m_text[i].c_str());
		}

	}

}

void BattleConsole::moveCursorToTopOfTextOutput() const {
	moveCursorToLowerBorder();
	Console::moveCursorDown(1);
}

void BattleConsole::moveCursorToLowerBorder() const {
	Console::moveCursorToRow(7);
	Console::moveCursorToCol();
}
