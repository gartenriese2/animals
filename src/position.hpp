#ifndef _POSITION_HPP
#define _POSITION_HPP

#include <string>

class Position {

	public:

		Position() {}
		Position(int x, int y) : m_x(x), m_y(y) {};

		void set(int x, int y) { m_x = x; m_y = y; }

		const int getX() const { return m_x; }
		const int getY() const { return m_y; }

		int & x() { return m_x; }
		int & y() { return m_y; }

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

		int m_x;
		int m_y;

};

#endif // _POSITION_HPP