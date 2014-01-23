#ifndef _BATTLECONSOLE_HPP
#define _BATTLECONSOLE_HPP

#include <string>
#include <deque>
#include <vector>

#include "console.hpp"

class BattleConsole {

	public:

		static void print();
		static void printAttacks(const std::vector<std::string> &, unsigned int = 0);

		static void addText(const std::string &);
		static void advanceText();
		static void emptyText();
		static bool textEmpty() { return instance().m_text.empty(); }

	private:

		BattleConsole();

		void printBorders() const;
		void printText() const;

		void moveCursorToTopOfTextOutput() const;
		void moveCursorToLowerBorder() const;

		static BattleConsole & instance() { static BattleConsole c; return c; }

		std::deque<std::string> m_text;
		unsigned int m_textWidth;
		unsigned int m_textHeight;

};

#endif // _BATTLECONSOLE_HPP