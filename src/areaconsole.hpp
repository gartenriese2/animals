#ifndef _AREACONSOLE_HPP
#define _AREACONSOLE_HPP

#include <memory>
#include <deque>
#include <string>

#include "console.hpp"
#include "typedefs.hpp"
#include "position.hpp"

class AreaConsole {

	public:

		static void print();

		static void setAreaBase(std::shared_ptr<std::vector<std::string>>);
		static void setPosition(std::shared_ptr<Position>);

		static void addText(const std::string &);
		static void addText(const std::vector<std::string> & vec);
		static void advanceText();
		static void emptyText();
		static bool textEmpty() { return instance().m_text.empty(); }

	private:

		AreaConsole();

		void printBorders() const;
		void printArea() const;
		void printText() const;

		void moveCursorToTopOfTextOutput() const;
		void moveCursorToLowerBorder() const;
		void moveCursorToBottomOfArea() const;
		void moveCursorToTopOfArea() const;
		void moveCursorToUpperBorder() const;

		static AreaConsole & instance() { static AreaConsole c; return c; }

		std::shared_ptr<std::vector<std::string>> m_area;
		std::shared_ptr<Position> m_pos;
		std::deque<std::string> m_text;

		unsigned int m_areaWidth;
		unsigned int m_areaHeight;
		unsigned int m_grassColor;

};

#endif // _AREACONSOLE_HPP