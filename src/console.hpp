#ifndef _CONSOLE_HPP
#define _CONSOLE_HPP

#include <deque>
#include <string>

#include "typedefs.hpp"

class Console {

	public:

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
		
		~Console() {}

	private:

		Console() {}

		void printTextLines();
		void printInputTextLines();
		void printWorldLines();
		void printEmptyWorld();
		void printBorders();

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

		

};

#endif // _CONSOLE_HPP