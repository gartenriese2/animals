#ifndef _CONSOLE_
#define _CONSOLE_

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
		static void resize();

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

		static void moveCursorTo(int = 0, int = 0);
		static void moveCursorToRow(int = 0);
		static void moveCursorToCol(int = 0);
		static void moveCursorUp(int = 1);
		static void moveCursorDown(int = 1);
		static void moveCursorRight(int = 1);
		static void moveCursorLeft(int = 1);
		static void moveCursorToNextLine();

		static void clearLine();
		static const std::vector<std::string> splitString(const std::string &, const unsigned int = 0);

		static unsigned int setColor(float, float, float, float = -1.f, float = -1.f, float = -1.f);
		static void useColor(unsigned int);
		static void unsetColor(unsigned int);

		static void printBorders();

	private:

		void createWindow();

		static Console & instance() { static Console c; return c; }

		WINDOW * m_win;

		unsigned int m_colorNum;

};

#endif // _CONSOLE_
