#include "console.hpp"

static constexpr unsigned int k_consoleWidth = 100;
static constexpr unsigned int k_consoleHeight = 30;

//
// STATIC
//

void Console::debug(const std::string & str) {
	
	move(0,0);
	std::string s =  "DEBUG: " + str;
	printw(s.c_str());

}

unsigned int Console::getConsoleHeight() {
	return k_consoleHeight;
}

unsigned int Console::getConsoleWidth() {
	return k_consoleWidth;
}

void Console::moveCursorToRow(unsigned int rows) {

	move(getmaxy(stdscr) - 1 - rows, getcurx(stdscr));

}

void Console::moveCursorToCol(unsigned int cols) {
	
	move(getcury(stdscr), cols);

}

void Console::moveCursorUp(unsigned int rows) {

	int col = getcurx(stdscr);
	int row = getcury(stdscr);
	move(row - rows, col);

}

void Console::moveCursorDown(unsigned int rows) {

	int col = getcurx(stdscr);
	int row = getcury(stdscr);
	move(row + rows, col);

}

void Console::moveCursorRight(unsigned int cols) {

	int col = getcurx(stdscr);
	int row = getcury(stdscr);
	move(row, col + cols);

}

void Console::moveCursorLeft(unsigned int cols) {

	int col = getcurx(stdscr);
	int row = getcury(stdscr);
	move(row, col - cols);

}

void Console::moveCursorToNextLine() {
	
	moveCursorDown();
	moveCursorToCol();

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
}

Console::~Console() {
	// end ncurses
	endwin();
}

void Console::printBorders() const {

	moveCursorToRow(k_consoleHeight - 1);
	moveCursorToCol();
	addstr("\u256D");
	for (unsigned int i = 0; i < k_consoleWidth - 2; ++i) {
		addstr("\u2500");
	}
	addstr("\u256E");
	for (unsigned int i = 0; i < k_consoleHeight - 2; ++i) {
		moveCursorToNextLine();
		addstr("\u2502");
		moveCursorToCol(k_consoleWidth - 1);
		addstr("\u2502");
	}
	moveCursorToNextLine();
	addstr("\u2570");
	for (unsigned int i = 0; i < k_consoleWidth - 2; ++i) {
		addstr("\u2500");
	}
	addstr("\u256F");

}
