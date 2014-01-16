#ifndef _POSITION_HPP
#define _POSITION_HPP

#include <string>

class Position {

	public:

		Position() {}
		Position(unsigned int x, unsigned int y) : m_x(x), m_y(y) {};

		void set(unsigned int x, unsigned int y) { m_x = x; m_y = y; }

		const unsigned int getX() const { return m_x; }
		const unsigned int getY() const { return m_y; }

		unsigned int & x() { return m_x; }
		unsigned int & y() { return m_y; }

		bool operator==(const Position & other) const {
			return (m_x == other.getX() && m_y == other.getY());
		}

		bool operator<(const Position & other) const {
			return (m_x < other.getX()) || (m_x == other.getX() && m_y < other.getY());
		}

		friend std::ostream & operator<<(std::ostream & output, const Position & pos) {
			std::string str = "(" + std::to_string(pos.getX()) + "|" + std::to_string(pos.getY()) + ")";
			output << str;
			return output;
		}

	private:

		unsigned m_x;
		unsigned m_y;

};

#endif // _POSITION_HPP