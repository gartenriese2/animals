#include "console.hpp"

#include <algorithm>
#include <iostream>
#include <locale.h>

static constexpr unsigned int k_maxConsoleWidth = 100;
static constexpr unsigned int k_maxConsoleHeight = 30;
static constexpr unsigned int k_minConsoleWidth = 40;
static constexpr unsigned int k_minConsoleHeight = 20;

//
// STATIC
//

void Console::debug(const std::string & str) {
	
	std::string s =  "DEBUG: " + str;
	wmove(stdscr,0,0);
	wclrtoeol(stdscr);
	wprintw(stdscr, s.c_str());
	wrefresh(stdscr);

}

unsigned int Console::getConsoleHeight() {
	
	unsigned int x,y;
	getmaxyx(win(), y, x);
	return std::min(k_maxConsoleHeight, y);

}

unsigned int Console::getConsoleWidth() {
	
	unsigned int x,y;
	getmaxyx(win(), y, x);
	return std::min(k_maxConsoleWidth, x);

}

void Console::moveCursorToRow(unsigned int rows) {

	wmove(win(), getmaxy(win()) - 1 - rows, getcurx(win()));

}

void Console::moveCursorToCol(unsigned int cols) {
	
	wmove(win(), getcury(win()), cols);

}

void Console::moveCursorUp(unsigned int rows) {

	int col = getcurx(win());
	int row = getcury(win());
	wmove(win(), row - rows, col);

}

void Console::moveCursorDown(unsigned int rows) {

	int col = getcurx(win());
	int row = getcury(win());
	wmove(win(), row + rows, col);

}

void Console::moveCursorRight(unsigned int cols) {

	int col = getcurx(win());
	int row = getcury(win());
	wmove(win(), row, col + cols);

}

void Console::moveCursorLeft(unsigned int cols) {

	int col = getcurx(win());
	int row = getcury(win());
	wmove(win(), row, col - cols);

}

void Console::moveCursorToNextLine() {
	
	moveCursorDown();
	moveCursorToCol();

}

void Console::moveCursorTo(unsigned int y, unsigned int x) {

	wmove(win(), y, x);

}

void Console::clearLine() {

	unsigned int x,y;
    getmaxyx(win(),y,x);

	unsigned int row = getcury(win());
	unsigned int col = getcurx(win());

	for (unsigned int i = 1; i < x - 1; ++i) {
		moveCursorTo(row, i);
		waddstr(win(), " ");
	}

	moveCursorTo(row, col);

}

void Console::printBorders() {

        unsigned int x,y;
        getmaxyx(win(),y,x);

        moveCursorTo();
        waddstr(win(), "\u256D");
        for (unsigned int i = 0; i < x - 2; ++i) {
                waddstr(win(), "\u2500");
        }
        waddstr(win(), "\u256E");
        
        for (unsigned int i = 0; i < y - 2; ++i) {
                waddstr(win(), "\u2502");
                moveCursorToCol(x - 1);
                waddstr(win(), "\u2502");
        }
        
        waddstr(win(), "\u2570");
        for (unsigned int i = 0; i < x - 2; ++i) {
                waddstr(win(), "\u2500");
        }
        waddstr(win(), "\u256F");

}

const std::vector<std::string> Console::splitString(const std::string & str) {

	std::vector<std::string> v;
	unsigned int width = getConsoleWidth() - 2;
	unsigned int pos = width;
	while (pos < str.size()) {
		v.emplace_back(str.substr(pos - width, width));
		pos += width;
	}
	v.emplace_back(str.substr(pos - width));

	return v;

}

//
// MEMBER
//

Console::Console() {
	
	// init ncurses
	setlocale(LC_ALL,"");
	initscr();
	noecho();
	curs_set(0);
	cbreak();

	unsigned int x,y;
	getmaxyx(stdscr,y,x);
	if (x < k_minConsoleWidth || y < k_minConsoleHeight) {
		endwin();
		std::cout << "Terminal too small!" << std::endl;
		if (x < k_minConsoleWidth) {
			std::cout << "Needs to be " << k_minConsoleWidth << " wide, but is " << x << " wide!" << std::endl;
		}
		if (y < k_minConsoleHeight) {
			std::cout << "Needs to be " << k_minConsoleHeight << " high, but is " << y << " high!" << std::endl;
		}
		exit(1);
	}

	unsigned int dX = std::min(x,k_maxConsoleWidth);
	unsigned int dY = std::min(y,k_maxConsoleHeight);
	unsigned int xStart = (x - dX) / 2;
	unsigned int yStart = (y - dY) / 2;

	m_win = newwin(dY, dX, yStart, xStart);
	keypad(m_win, TRUE);
	wrefresh(m_win);

}

Console::~Console() {
	
	// end ncurses
	delwin(m_win);
	endwin();

}
