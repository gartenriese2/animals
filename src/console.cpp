#include "console.hpp"

#include <iostream>

static constexpr unsigned int k_outputLines = 2;
static constexpr unsigned int k_worldY = 20;
static constexpr unsigned int k_worldX = 50;

void Console::debug(const std::string & str) {
	
	move(0,0);
	std::string s =  "DEBUG: " + str;
	printw(s.c_str());

}

// void Console::print() {

// 	instance().printWorldLines();
// 	instance().printBorders();
// 	instance().printTextLines();
// 	refresh();
	
// }

// void Console::printText() {
// 	instance().printTextLines();
// 	refresh();
// }

// void Console::printInputText() {
// 	instance().printInputTextLines();
// 	refresh();
// }

// void Console::printArea() {
// 	instance().printWorldLines();
// 	refresh();
// }

// void Console::clearArea() {
// 	instance().printEmptyWorld();
// 	refresh();
// }

// void Console::setAreaBase(const twoDimArray & arr) {
// 	instance().m_area = arr;
// }

// void Console::setPosition(const Position & pos) {
// 	instance().m_pos = pos;
// }

// void Console::toggleMenu() {
// 	if (instance().m_menu.isActive()) {
// 		instance().m_menu.deactivate();
// 	} else {
// 		instance().m_menu.activate();
// 	}
// }

// bool Console::activeMenu() {
// 	return instance().m_menu.isActive();
// }

// void Console::printMenu() {
// 	instance().printMenuInstance();
// }


Console::Console()
  : m_menu({"Animals","Empty","Empty2"})
{
	// init ncurses
	setlocale(LC_ALL,"");
	initscr();
	noecho();
	curs_set(0);
}

Console::~Console() {
	// end ncurses
	endwin();
}

// void Console::printTextLines() {

// 	for (unsigned int i = 0; i < k_outputLines; ++i) {
// 		std::cout << "\033[1A" << "\r\033[K";
// 	}
// 	unsigned int count = 0;
// 	for (int i = k_outputLines - 1; i >= 0; --i) {
// 		if (count >= m_outputList.size()) {
// 			std::cout << "" << std::endl;
// 		} else {
// 			std::cout << m_outputList[count++] << std::endl;
// 		}
// 	}

// }



// void Console::printInputTextLines() {

// 	std::cout << "\r\033[K";

// 	std::cout << m_inputText;

// }

// void Console::printEmptyWorld() {

// 	printBorders();
// 	moveCursorToTopOfArea();
// 	for (unsigned int i = 0; i < k_worldY; ++i) {
// 		std::cout << "\033[K\n";
// 	}


// }

// void Console::printWorldLines() {

// 	moveCursorToTopOfArea();

// 	int fromY = static_cast<int>(m_pos.getY()) - static_cast<int>(k_worldY) / 2;
// 	int toY = fromY + static_cast<int>(k_worldY);
// 	int fromX = static_cast<int>(m_pos.getX()) - static_cast<int>(k_worldX) / 2;
// 	int toX = fromX + static_cast<int>(k_worldX);

// 	for (int i = fromY; i < toY; ++i) {
		
// 		std::cout << "\r\033[K";

// 		if (i >= 0 && i < m_area.size()) {
					
// 			for (int j = fromX; j < toX; ++j) {
// 				if (j < 0 || j >= m_area[i].size()) {
// 					std::cout << " ";
// 				} else if (i == m_pos.getY() && j == m_pos.getX()) {
// 					std::cout << "P";
// 				} else {
// 					std::cout << m_area[i][j];
// 				}
// 			}

// 		}

// 		std::cout << std::endl;
		
// 	}

// }

// void Console::printMenuInstance() {

// 	moveCursorToTopOfArea();
	
// 	for (const auto & s : m_menu.getEntries()) {
// 		std::cout << "\033[" << k_worldX + 1 << "G";
// 		if (s == m_menu.getActiveEntry()) {
// 			std::cout << "-->";
// 		}
// 		std::cout << s;
// 		std::cout << "\033[1B";
// 	}

// }

void Console::moveCursorToRow(unsigned int rows) {

	move(getmaxy(stdscr) - 1 - rows, getcurx(stdscr));

}

void Console::moveCursorToCol(unsigned int cols) {
	
	move(getcury(stdscr), cols);

}

void Console::moveCursorUp(unsigned int rows) {

	int col = getcury(stdscr);
	int row = getcury(stdscr);
	move(row - 1, col);

}

void Console::moveCursorDown(unsigned int rows) {

	int col = getcury(stdscr);
	int row = getcury(stdscr);
	move(row + 1, col);

}

void Console::moveCursorRight(unsigned int cols) {

	int col = getcury(stdscr);
	int row = getcury(stdscr);
	move(row, col + 1);

}

void Console::moveCursorLeft(unsigned int cols) {

	int col = getcury(stdscr);
	int row = getcury(stdscr);
	move(row, col - 1);

}

void Console::moveCursorToNextLine() {
	
	moveCursorDown();
	moveCursorToCol();

}
