#ifndef _CONSOLE_HPP
#define _CONSOLE_HPP

#include <ncursesw/ncurses.h>
#include <locale.h>
#include <string>

#define DEB(x) Console::debug(x)

class Console {

	public:

		static void debug(const std::string &); 
		
		Console();
		~Console();

	protected:

		static unsigned int getConsoleHeight();
		static unsigned int getConsoleWidth();

		static void moveCursorToRow(unsigned int = 0);
		static void moveCursorToCol(unsigned int = 0);
		static void moveCursorUp(unsigned int = 1);
		static void moveCursorDown(unsigned int = 1);
		static void moveCursorRight(unsigned int = 1);
		static void moveCursorLeft(unsigned int = 1);
		static void moveCursorToNextLine();

		virtual void printBorders() const;

	private:

		static Console & instance() { static Console c; return c; }		

};

#endif // _CONSOLE_HPP