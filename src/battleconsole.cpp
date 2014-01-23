#include "battleconsole.hpp"

#include <vector>

#include "io.hpp"

//
// STATIC
//

void BattleConsole::print() {

	instance().printBorders();
	instance().printText();

	wrefresh(win());

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
	m_textWidth = getConsoleWidth() - 10;

}

void BattleConsole::printBorders() const {

	Console::printBorders();
	moveCursorToLowerBorder();

	waddstr(win(), "\u251C");
	for (unsigned int i = 0; i < Console::getConsoleWidth() - 2; ++i) {
		waddstr(win(), "\u2500");
	}
	waddstr(win(), "\u2524");

}

void BattleConsole::printText() const {

	for (unsigned int i = 0; i < m_textHeight; ++i) {
		
		moveCursorToTopOfTextOutput();
		moveCursorDown(i);
		moveCursorRight();

		clearLine();

		if (m_text.size() > i) {
			moveCursorRight((getConsoleWidth() - 2 - m_text[i].size()) / 2);
			wprintw(win(),m_text[i].c_str());
		}

	}

}

void BattleConsole::moveCursorToTopOfTextOutput() const {
	moveCursorToRow(Console::getConsoleHeight() * 2 / 3);
	moveCursorToCol();
}

void BattleConsole::moveCursorToLowerBorder() const {
	moveCursorToRow(Console::getConsoleHeight() / 3);
	moveCursorToCol();
}
