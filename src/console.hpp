#ifndef _CONSOLE_HPP
#define _CONSOLE_HPP

#include <deque>
#include <string>
#include <ncursesw/ncurses.h>
#include <locale.h>

#include "typedefs.hpp"
#include "menu.hpp"

#define DEB(x) Console::debug(x)

class Console {

	public:

		static void debug(const std::string &); 
		

		// static void toggleMenu();
		// static void printMenu();
		// static bool activeMenu();
		// static void goMenuUp() { instance().m_menu.activateUpperEntry(); }
		// static void goMenuDown() { instance().m_menu.activateLowerEntry(); }
		
		Console();
		~Console();

	protected:

		static void moveCursorToRow(unsigned int = 0);
		static void moveCursorToCol(unsigned int = 0);
		static void moveCursorUp(unsigned int = 1);
		static void moveCursorDown(unsigned int = 1);
		static void moveCursorRight(unsigned int = 1);
		static void moveCursorLeft(unsigned int = 1);
		static void moveCursorToNextLine();

	private:

		

		// void printTextLines();
		// void printInputTextLines();
		// void printWorldLines();
		// void printEmptyWorld();
		// void printBorders();
		// void printMenuInstance();

		static Console & instance() { static Console c; return c; }

		
		std::string m_inputText;
		

		Menu m_menu;

		

};

#endif // _CONSOLE_HPP