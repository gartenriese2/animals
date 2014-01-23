#include "areaconsole.hpp"

#include "io.hpp"

static constexpr unsigned int k_textHeight = 2;

//
// STATIC
//

void AreaConsole::print() {

	Console::clear();

	instance().printBorders();
	instance().printArea();
	instance().printText();

	Console::refresh();

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

	m_areaHeight = Console::getHeight() - 3 - k_textHeight;
	m_areaWidth = Console::getWidth() - 2;

}

void AreaConsole::printBorders() const {

	Console::printBorders();
	moveCursorToLowerBorder();

	waddstr(Console::win(), "\u251C");
	for (unsigned int i = 0; i < Console::getWidth() - 2; ++i) {
		waddstr(Console::win(), "\u2500");
	}
	waddstr(Console::win(), "\u2524");

}

void AreaConsole::printArea() const {

	moveCursorToTopOfArea();

	int fromY = static_cast<int>(m_pos->getY()) - static_cast<int>(m_areaHeight) / 2;
	int toY = fromY + static_cast<int>(m_areaHeight);
	int fromX = static_cast<int>(m_pos->getX()) - static_cast<int>(m_areaWidth) / 2;
	int toX = fromX + static_cast<int>(m_areaWidth);

	

	for (int i = fromY; i < toY; ++i) {

		Console::clearLine();
		Console::moveCursorToCol(1);

		if (i >= 0 && i < m_area->size()) {
					
			for (int j = fromX; j < toX; ++j) {

				if (j < 0 || j >= (* m_area)[i].size()) {
					wprintw(Console::win(), " ");
				} else if (i == m_pos->getY() && j == m_pos->getX()) {
					wprintw(Console::win(), "P");
				} else {
					
					char c = (* m_area)[i][j];
					if (c == '#') {
						init_color(90, 1000, 1000, 0);
						init_pair(1, 90, -1);
						wattron(Console::win(), COLOR_PAIR(1));
					}

					std::string s(1, c);
					wprintw(Console::win(), s.c_str());
					wattroff(Console::win(), COLOR_PAIR(1));

				}

			}

		}

		Console::moveCursorToNextLine();
		
	}

}

void AreaConsole::printText() const {

	for (unsigned int i = 0; i < k_textHeight; ++i) {
		
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

void AreaConsole::moveCursorToTopOfTextOutput() const {
	Console::moveCursorToRow(k_textHeight);
	Console::moveCursorToCol();
}

void AreaConsole::moveCursorToLowerBorder() const {
	Console::moveCursorToRow(k_textHeight + 1);
	Console::moveCursorToCol();
}

void AreaConsole::moveCursorToTopOfArea() const {
	Console::moveCursorToRow(k_textHeight + m_areaHeight + 1);
	Console::moveCursorToCol();
}

void AreaConsole::moveCursorToUpperBorder() const {
	Console::moveCursorToRow(k_textHeight + m_areaHeight + 2);
	Console::moveCursorToCol();
}
