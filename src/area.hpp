#ifndef _AREA_HPP
#define _AREA_HPP

#include <array>
#include <tuple>
#include <map>
#include <string>

#include "position.hpp"

static constexpr unsigned int k_height = 10;
static constexpr unsigned int k_width = 50;

using portalMap = std::map<Position, std::string>;
using twoDimArr = std::array<std::array<char, k_width>, k_height>;

enum AreaType : char { BORDER = '+', GRASS = '#', PORTAL = 'o', HEALING = 'H', WATER = '~' };

class Area {
	
	public:

		Area();
		Area(const std::string &, const twoDimArr &, const portalMap &);
		~Area();

		const std::string & getName() const { return m_name; }
		const twoDimArr & getBase() const { return m_base; }
		const Position & getPortalPos(const std::string &) const;
		const Area & getAreaFromPortalPos(const Position &);

		static Area & getArea(const std::string &);
		static const unsigned int getHeight() { return k_height; }

	private:

		std::string m_name;
		twoDimArr m_base;
		portalMap m_portals;

		static std::map<std::string, Area> & getAreas();

};

#endif // _AREA_HPP