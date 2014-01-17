#ifndef _CONSOLE_HPP
#define _CONSOLE_HPP

#include <deque>
#include <string>

#include "typedefs.hpp"
#include "menu.hpp"

#define DEB(x) Console::debug(x)

class Console {

	public:

		static void debug(const std::string &); 

		static void print();

		static void printText();
		static void printInputText();
		static void printAllText() { printText(); printInputText(); }
		static void addText(const std::string &);
		static void setInputText(const std::string &);
		static void advanceText();
		static bool textEmpty();

		static void printArea();
		static void clearArea();
		static void setAreaBase(const twoDimArray &);
		static void setPosition(const Position &);

		static void toggleMenu();
		static void printMenu();
		static bool activeMenu();
		static void goMenuUp() { instance().m_menu.activateUpperEntry(); }
		static void goMenuDown() { instance().m_menu.activateLowerEntry(); }
		
		~Console() {}

	private:

		Console();

		void printTextLines();
		void printInputTextLines();
		void printWorldLines();
		void printEmptyWorld();
		void printBorders();
		void printMenuInstance();

		void moveCursorToBottom();
		void moveCursorToBottomOfTextOutput();
		void moveCursorToLowerBorder();
		void moveCursorToBottomOfArea();
		void moveCursorToTopOfArea();
		void moveCursorToUpperBorder();

		static Console & instance() { static Console c; return c; }

		std::deque<std::string> m_outputList;
		std::string m_inputText;
		twoDimArray m_area;
		Position m_pos;

		Menu m_menu;

		

};

#endif // _CONSOLE_HPP