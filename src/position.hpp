#ifndef _POSITION_HPP
#define _POSITION_HPP

#include <string>

template <typename T>
class TPosition {

	public:

		TPosition() {}
		TPosition(T x, T y) : m_x(x), m_y(y) {};

		void set(T x, T y) { m_x = x; m_y = y; }

		T getX() const { return m_x; }
		T getY() const { return m_y; }

		T & x() { return m_x; }
		T & y() { return m_y; }

		bool operator==(const TPosition & other) const {
			return (m_x == other.m_x && m_y == other.m_y);
		}

		bool operator<(const TPosition & other) const {
			return (m_x < other.m_x) || (m_x == other.m_x && m_y < other.m_y);
		}

		friend std::ostream & operator<<(std::ostream & output, const TPosition & pos) {
			std::string str = "(" + std::to_string(pos.m_x) + "|" + std::to_string(pos.m_y) + ")";
			output << str;
			return output;
		}

	private:

		T m_x;
		T m_y;

};

using Position = TPosition<int>;
using Position_unsigned = TPosition<unsigned int>;

#endif // _POSITION_HPP
