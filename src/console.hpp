#ifndef _CONSOLE_HPP
#define _CONSOLE_HPP

#include <ncursesw/ncurses.h>
#include <string>
#include <vector>

#include "io.hpp"
class AreaConsole;
class BattleConsole;
class TextConsole;

#define DEB(x) Console::debug(x)
#define EXIT(x) Console::end(x)

class Console {

	public:

		static void debug(const std::string &); 
		static void end(const std::string &);

		static WINDOW * win() { return instance().m_win; }
		static void refresh() { wrefresh(win()); }

		static void clear();
		
		Console();
		~Console();

	protected:

		friend IO;
		friend AreaConsole;
		friend BattleConsole;
		friend TextConsole;

		static unsigned int getHeight();
		static unsigned int getWidth();
		static unsigned int getMinWidth();

		static void moveCursorTo(unsigned int = 0, unsigned int = 0);
		static void moveCursorToRow(unsigned int = 0);
		static void moveCursorToCol(unsigned int = 0);
		static void moveCursorUp(unsigned int = 1);
		static void moveCursorDown(unsigned int = 1);
		static void moveCursorRight(unsigned int = 1);
		static void moveCursorLeft(unsigned int = 1);
		static void moveCursorToNextLine();

		static void clearLine();
		static const std::vector<std::string> splitString(const std::string &, const unsigned int = 0);

		static unsigned int setColor(float, float, float, float = -1.f, float = -1.f, float = -1.f);
		static void useColor(unsigned int);
		static void unsetColor(unsigned int);

		static void printBorders();

	private:

		static Console & instance() { static Console c; return c; }

		WINDOW * m_win;

		unsigned int colorNum;

};

#endif // _CONSOLE_HPP