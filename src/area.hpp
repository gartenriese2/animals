#ifndef _AREA_HPP
#define _AREA_HPP

#include <array>
#include <tuple>
#include <map>
#include <string>

#include "position.hpp"
#include "areadatabasereader.hpp"

static constexpr unsigned int k_height = 10;
static constexpr unsigned int k_width = 50;

using portalMap = std::map<Position, std::string>;
using twoDimArray = std::array<std::array<char, k_width>, k_height>;

enum AreaType : char { BORDER = '+', GRASS = '#', PORTAL = 'o', HEALING = 'H', WATER = '~' };

class Area {
	
	public:

		Area();
		Area(const std::string &, const twoDimArray &, const portalMap &);
		~Area();

		const std::string & getName() const { return m_name; }
		const twoDimArray & getBase() const { return m_base; }
		const Position & getPortalPos(const std::string &) const;
		const Area & getAreaFromPortalPos(const Position &);

		static Area & getArea(const std::string &);
		static const unsigned int getHeight() { return k_height; }

	private:

		std::string m_name;
		twoDimArray m_base;
		portalMap m_portals;

		twoDimArray convertStringToTwoDimArr(const std::string &) const;

		static std::map<std::string, Area> & getAreas();

};

#endif // _AREA_HPP