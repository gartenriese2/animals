#ifndef _AREA_HPP
#define _AREA_HPP

#include <array>
#include <tuple>
#include <map>
#include <string>

template <class T, size_t ROW, size_t COL>
using twoDimArr = std::array<std::array<T, COL>, ROW>;

static constexpr unsigned int k_height = 10;
static constexpr unsigned int k_width = 20;

enum AreaType : char { BORDER = '+', GRASS = '#', PORTAL = 'o' };

class Area {
	
	public:

		Area();
		Area(const std::string &, const twoDimArr<char,k_height,k_width> &);
		~Area();

		void print() const;

		const std::string & getName() const { return m_name; }
		void setPlayerPos(unsigned int, unsigned int);
		const std::tuple<unsigned int, unsigned int> & getPlayerPos() const { return m_playerPos; }
		void addPortal(const std::tuple<unsigned int, unsigned int>, std::shared_ptr<Area>);
		const std::tuple<unsigned int, unsigned int> & getPortalPos(const std::string &) const;

	private:

		std::string m_name;
		twoDimArr<char,k_height,k_width> m_base;
		std::tuple<unsigned int, unsigned int> m_playerPos;
		std::map<std::tuple<unsigned int, unsigned int>, std::shared_ptr<Area>> m_portals;

};

#endif // _AREA_HPP