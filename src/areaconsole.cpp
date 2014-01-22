#include "areaconsole.hpp"

#include "io.hpp"

static constexpr unsigned int k_textHeight = 2;

//
// STATIC
//

void AreaConsole::print() {

	instance().printBorders();
	instance().printArea();
	instance().printText();

	wrefresh(win());

}

void AreaConsole::setAreaBase(std::shared_ptr<twoDimArray> ptr) {
	instance().m_area = ptr;
}

void AreaConsole::setPosition(std::shared_ptr<Position> ptr) {
	instance().m_pos = ptr;
}

void AreaConsole::addText(const std::string & str) {
	
	std::vector<std::string> vec = Console::splitString(str);
	for (const auto i : vec) {
		instance().m_text.emplace_back(i);
	}

}

void AreaConsole::advanceText() {
	if (instance().m_text.size() > 0) {
		instance().m_text.pop_front();
	}
}

void AreaConsole::emptyText() {

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

AreaConsole::AreaConsole() {

	m_areaHeight = getConsoleHeight() - 3 - k_textHeight;
	m_areaWidth = getConsoleWidth() - 2;

}

void AreaConsole::printBorders() const {

	Console::printBorders();
	moveCursorToLowerBorder();

	waddstr(win(), "\u251C");
	for (unsigned int i = 0; i < Console::getConsoleWidth() - 2; ++i) {
		waddstr(win(), "\u2500");
	}
	waddstr(win(), "\u2524");

}

void AreaConsole::printArea() const {

	moveCursorToTopOfArea();

	int fromY = static_cast<int>(m_pos->getY()) - static_cast<int>(m_areaHeight) / 2;
	int toY = fromY + static_cast<int>(m_areaHeight);
	int fromX = static_cast<int>(m_pos->getX()) - static_cast<int>(m_areaWidth) / 2;
	int toX = fromX + static_cast<int>(m_areaWidth);

	for (int i = fromY; i < toY; ++i) {

		std::string line;

		if (i >= 0 && i < m_area->size()) {
					
			for (int j = fromX; j < toX; ++j) {

				if (j < 0 || j >= (* m_area)[i].size()) {
					line += " ";
				} else if (i == m_pos->getY() && j == m_pos->getX()) {
					line += "P";
				} else {
					line += (* m_area)[i][j];
				}

			}

		}

		clearLine();
		moveCursorToCol(1);
		wprintw(win(), line.c_str());

		moveCursorToNextLine();
		
	}

}

void AreaConsole::printText() const {

	for (unsigned int i = 0; i < k_textHeight; ++i) {
		
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

void AreaConsole::moveCursorToTopOfTextOutput() const {
	moveCursorToRow(k_textHeight);
	moveCursorToCol();
}

void AreaConsole::moveCursorToLowerBorder() const {
	moveCursorToRow(k_textHeight + 1);
	moveCursorToCol();
}

void AreaConsole::moveCursorToTopOfArea() const {
	moveCursorToRow(k_textHeight + m_areaHeight + 1);
	moveCursorToCol();
}

void AreaConsole::moveCursorToUpperBorder() const {
	moveCursorToRow(k_textHeight + m_areaHeight + 2);
	moveCursorToCol();
}
