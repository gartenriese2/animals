#ifndef _AREA_HPP
#define _AREA_HPP

#include <array>
#include <tuple>

template <class T, size_t ROW, size_t COL>
using twoDimArr = std::array<std::array<T, COL>, ROW>;

static constexpr unsigned int k_height = 10;
static constexpr unsigned int k_width = 10;

enum AreaType : char { BORDER = '+', GRASS = '#' };

class Area {
	
	public:

		Area();
		Area(const twoDimArr<char,k_height,k_width> &);
		~Area();

		void print() const;

		void setPlayerPos(unsigned int, unsigned int);
		const std::tuple<unsigned int, unsigned int> & getPlayerPos() const { return m_playerPos; }

	private:

		twoDimArr<char,k_height,k_width> m_base;
		std::tuple<unsigned int, unsigned int> m_playerPos;

};

#endif // _AREA_HPP