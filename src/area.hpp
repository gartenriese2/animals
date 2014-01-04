#ifndef _AREA_HPP
#define _AREA_HPP

#include <array>
#include <tuple>
#include <map>

template <class T, size_t ROW, size_t COL>
using twoDimArr = std::array<std::array<T, COL>, ROW>;

static constexpr unsigned int k_height = 10;
static constexpr unsigned int k_width = 10;

enum AreaType : char { BORDER = '+', GRASS = '#', PORTAL = 'o' };

class Area {
	
	public:

		Area();
		Area(const twoDimArr<char,k_height,k_width> &);
		~Area();

		void print() const;

		void setPlayerPos(unsigned int, unsigned int);
		const std::tuple<unsigned int, unsigned int> & getPlayerPos() const { return m_playerPos; }
		void addPortal(const std::tuple<unsigned int, unsigned int>, std::shared_ptr<Area>);

	private:

		twoDimArr<char,k_height,k_width> m_base;
		std::tuple<unsigned int, unsigned int> m_playerPos;
		std::map<std::tuple<unsigned int, unsigned int>, std::shared_ptr<Area>> m_portals;

};

#endif // _AREA_HPP