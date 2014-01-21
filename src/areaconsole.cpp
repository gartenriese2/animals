#include "areaconsole.hpp"

#include "io.hpp"

static constexpr unsigned int k_outputRows = 2;
static constexpr unsigned int k_areaRows = 20;
static constexpr unsigned int k_areaColumns = 50;

//
// STATIC
//

void AreaConsole::print() {

	instance().printBorders();
	instance().printArea();
	instance().printText();
	refresh();

}

void AreaConsole::setAreaBase(std::shared_ptr<twoDimArray> ptr) {
	instance().m_area = ptr;
}

void AreaConsole::setPosition(std::shared_ptr<Position> ptr) {
	instance().m_pos = ptr;
}

void AreaConsole::addText(const std::string & str) {
	instance().m_text.emplace_back(str);
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
			refresh();
		}

	}

}

//
// MEMBER
//

void AreaConsole::printBorders() const {

	std::string border;
	for (unsigned int i = 0; i < k_areaColumns; ++i) {
		border += "\u2550";
	}

	moveCursorToLowerBorder();

	addstr("\u2521");
	printw(border.c_str());
	addstr("\u2529");

	moveCursorToUpperBorder();

	addstr("\u250F");
	printw(border.c_str());
	addstr("\u2513");

	for (unsigned int i = 0; i < k_areaRows; ++i) {
		moveCursorDown();
		moveCursorToCol(k_areaColumns + 1);
		addstr("\u2503");
		
	}

	moveCursorToUpperBorder();

	for (unsigned int i = 0; i < k_areaRows; ++i) {
		moveCursorDown();
		moveCursorToCol();
		addstr("\u2503");
		
	}

}

void AreaConsole::printArea() const {

	moveCursorToTopOfArea();

	int fromY = static_cast<int>(m_pos->getY()) - static_cast<int>(k_areaRows) / 2;
	int toY = fromY + static_cast<int>(k_areaRows);
	int fromX = static_cast<int>(m_pos->getX()) - static_cast<int>(k_areaColumns) / 2;
	int toX = fromX + static_cast<int>(k_areaColumns);

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

		moveCursorToCol(1);
		printw(line.c_str());

		moveCursorToNextLine();
		
	}

}

void AreaConsole::printText() const {

	moveCursorToTopOfTextOutput();

	unsigned int count = 0;
	for (int i = k_outputRows - 1; i >= 0; --i) {

		if (count < m_text.size()) {
			moveCursorToCol(1);
			printw(m_text[count++].c_str());
		}
		
		moveCursorToNextLine();

	}

}

void AreaConsole::moveCursorToTopOfTextOutput() const {
	moveCursorToRow(k_outputRows - 1);
	moveCursorToCol();
}

void AreaConsole::moveCursorToLowerBorder() const {
	moveCursorToRow(k_outputRows);
	moveCursorToCol();
}

void AreaConsole::moveCursorToTopOfArea() const {
	moveCursorToRow(k_outputRows + k_areaRows);
	moveCursorToCol();
}

void AreaConsole::moveCursorToUpperBorder() const {
	moveCursorToRow(k_outputRows + k_areaRows + 1);
	moveCursorToCol();
}
