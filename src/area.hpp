#ifndef _AREA_HPP
#define _AREA_HPP

#include <array>
#include <tuple>
#include <map>
#include <string>

#include "position.hpp"
#include "areadatabasereader.hpp"
#include "typedefs.hpp"
#include "animal.hpp"
#include "npchar.hpp"

enum AreaType : char { BORDER = '+', GRASS = '#', PORTAL = 'o', HEALING = 'H', WATER = '~', NPC = 'N' };

class Area {
	
	public:

		Area();
		Area(const std::string &, const twoDimArray &, const portalMap &,
			const likelyhoodTuples &, const portalMap &);
		~Area();

		void print(const Position & pos) const;

		const std::string & getName() const { return m_name; }
		const twoDimArray & getBase() const { return m_base; }
		const Position & getPortalPos(const std::string &) const;
		const Area getAreaFromPortalPos(const Position &);
		const NPChar getNPC(const Position &);

		Animal getWildAnimal() const;

		static const Area getArea(const std::string &);
		static const unsigned int getHeight() { return k_height; }

	private:

		std::string m_name;
		twoDimArray m_base;
		portalMap m_portals;
		likelyhoodTuples m_likelyhoods;
		portalMap m_npcs;

};

#endif // _AREA_HPP