#include "console.hpp"

#include <algorithm>
#include <iostream>
#include <locale.h>
#include <cassert>

static constexpr unsigned int k_maxConsoleWidth = 100;
static constexpr unsigned int k_maxConsoleHeight = 30;
static constexpr unsigned int k_minConsoleWidth = 40;
static constexpr unsigned int k_minConsoleHeight = 20;

//
// STATIC
//

void Console::debug(const std::string & str) {

	std::string s =  "DEBUG: " + str;
	wmove(stdscr, 0, 0);
	wclrtoeol(stdscr);
	wprintw(stdscr, s.c_str());
	wrefresh(stdscr);

}

void Console::end(const std::string & str) {

	delwin(win());
	endwin();

	std::cout << str << std::endl;
	exit(EXIT_FAILURE);

}

void Console::resize() {

	Console::clear();
	werase(stdscr);

	instance().createWindow();

	Console::refresh();
	wrefresh(stdscr);

}

unsigned int Console::getHeight() {

	unsigned int x,y;
	getmaxyx(win(), y, x);
	return std::min(k_maxConsoleHeight, y);

}

unsigned int Console::getWidth() {

	unsigned int x,y;
	getmaxyx(win(), y, x);
	return std::min(k_maxConsoleWidth, x);

}

unsigned int Console::getMinWidth() {

	return k_minConsoleWidth;

}

void Console::moveCursorToRow(int rows) {

	assert(rows >= 0);
	wmove(win(), getmaxy(win()) - 1 - static_cast<int>(rows), getcurx(win()));

}

void Console::moveCursorToCol(int cols) {

	assert(cols >= 0);
	wmove(win(), getcury(win()), static_cast<int>(cols));

}

void Console::moveCursorUp(int rows) {

	assert(rows >= 0);
	const auto col = getcurx(win());
	const auto row = getcury(win());
	wmove(win(), row - rows, col);

}

void Console::moveCursorDown(int rows) {

	assert(rows >= 0);
	const auto col = getcurx(win());
	const auto row = getcury(win());
	wmove(win(), row + rows, col);

}

void Console::moveCursorRight(int cols) {

	assert(cols >= 0);
	const auto col = getcurx(win());
	const auto row = getcury(win());
	wmove(win(), row, col + cols);

}

void Console::moveCursorLeft(int cols) {

	assert(cols >= 0);
	const auto col = getcurx(win());
	const auto row = getcury(win());
	wmove(win(), row, col - cols);

}

void Console::moveCursorToNextLine() {

	moveCursorDown();
	moveCursorToCol();

}

void Console::moveCursorTo(int y, int x) {

	assert(y >= 0 && x >= 0);
	wmove(win(), y, x);

}

void Console::clear() {

	werase(win());

}

void Console::clearLine() {

	int x,y;
	getmaxyx(win(), y, x);

	const auto row = getcury(win());
	const auto col = getcurx(win());

	for (int i = 1; i < x - 1; ++i) {

		moveCursorTo(row, i);
		waddstr(win(), " ");

	}

	moveCursorTo(row, col);

}

void Console::printBorders() {

	int x,y;
	getmaxyx(win(), y, x);

	moveCursorTo();

	waddstr(win(), "\u256D");
	for (int i = 0; i < x - 2; ++i) {

		waddstr(win(), "\u2500");

	}
	waddstr(win(), "\u256E");

	for (int i = 0; i < y - 2; ++i) {

		waddstr(win(), "\u2502");
		moveCursorToCol(x - 1);
		waddstr(win(), "\u2502");

	}

	waddstr(win(), "\u2570");
	for (int i = 0; i < x - 2; ++i) {

		waddstr(win(), "\u2500");

	}
	waddstr(win(), "\u256F");

}

const std::vector<std::string> Console::splitString(const std::string & str, const unsigned int w) {

	std::vector<std::string> v;
	const unsigned int width = (w == 0 ? getWidth() - 2 : w);

	unsigned int pos = width;
	while (pos < str.size()) {

		v.emplace_back(str.substr(pos - width, width));
		pos += width;

	}

	v.emplace_back(str.substr(pos - width));

	return v;

}

float clamp(float value) {

	const auto temp = value + 1.f - std::abs(value - 1.f);
	return (temp + std::abs(temp)) * 0.25f;

}

unsigned int Console::setColor(float r, float g, float b, float r2, float g2, float b2) {

	const auto bkgd = !(r2 == -1.f || g2 == -1.f || b2 == -1.f);

	clamp(r);
	clamp(g);
	clamp(b);
	clamp(r2);
	clamp(g2);
	clamp(b2);

	init_color(static_cast<short>(instance().m_colorNum * 2), static_cast<short>(r * 1000.f),
		static_cast<short>(g * 1000.f), static_cast<short>(b * 1000.f));
	init_color(static_cast<short>(instance().m_colorNum * 2 + 1), static_cast<short>(r2 * 1000.f),
		static_cast<short>(g2 * 1000.f), static_cast<short>(b2 * 1000.f));

	if(bkgd) {
		init_pair(static_cast<short>(instance().m_colorNum), static_cast<short>(instance().m_colorNum * 2),
			static_cast<short>(instance().m_colorNum * 2 + 1));
	} else {
		init_pair(static_cast<short>(instance().m_colorNum), static_cast<short>(instance().m_colorNum * 2), -1);
	}

	return ++instance().m_colorNum - 1;

}

void Console::useColor(unsigned int pair) {

	wattron(win(), COLOR_PAIR(pair));

}

void Console::unsetColor(unsigned int pair) {

	wattroff(win(), COLOR_PAIR(pair));

}

//
// MEMBER
//

Console::Console()
  : m_colorNum{1}
{

	// init ncurses
	setlocale(LC_ALL, "");
	initscr();
	noecho();
	curs_set(0);
	cbreak();

	if(has_colors() == FALSE) {

		endwin();
		std::cout << "Your terminal does not support color" << std::endl;
		exit(EXIT_FAILURE);

	}

	start_color();
	use_default_colors();

	createWindow();

}

Console::~Console() {

	// end ncurses
	delwin(m_win);
	endwin();

}

void Console::createWindow() {

	unsigned int x,y;
	getmaxyx(stdscr, y, x);

	if (x < k_minConsoleWidth || y < k_minConsoleHeight) {

		endwin();

		std::cout << "Terminal too small!" << std::endl;
		if (x < k_minConsoleWidth) {
			std::cout << "Needs to be " << k_minConsoleWidth << " wide, but is " << x << " wide!" << std::endl;
		}
		if (y < k_minConsoleHeight) {
			std::cout << "Needs to be " << k_minConsoleHeight << " high, but is " << y << " high!" << std::endl;
		}

		exit(EXIT_FAILURE);

	}

	const auto dX = static_cast<int>(std::min(x,k_maxConsoleWidth));
	const auto dY = static_cast<int>(std::min(y,k_maxConsoleHeight));
	const int xStart = (static_cast<int>(x) - dX) / 2;
	const int yStart = (static_cast<int>(y) - dY) / 2;

	m_win = newwin(dY, dX, yStart, xStart);
	keypad(m_win, TRUE);
	wrefresh(m_win);

}
