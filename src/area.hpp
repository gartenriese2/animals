#ifndef _AREA_HPP
#define _AREA_HPP

#include <array>
#include <tuple>
#include <map>
#include <string>

#include "position.hpp"
#include "database/areadatabasereader.hpp"
#include "typedefs.hpp"
#include "animal.hpp"
#include "npchar.hpp"

enum AreaType : char { BORDER = '+', GRASS = '#', PORTAL = 'o', HEALING = 'H', WATER = '~', NPC = 'N' };

class Area {

	public:

		Area();
		// Area(const std::string &, const twoDimArray &, const portalMap &,
		// 	const likelyhoodTuples &, const portalMap &);
		Area(const std::string &, const std::vector<std::string> &, const portalMap &,
			const likelyhoodTuples &, const portalMap &);
		~Area();

		void print(const Position & pos) const;

		const std::string & getName() const { return m_name; }
		// const twoDimArray & getBase() const { return m_base; }
		const std::vector<std::string> & getBase() const { return m_base; }
		const Position_unsigned & getPortalPos(const std::string &) const;
		const Area getAreaFromPortalPos(const Position_unsigned &);
		const NPChar getNPC(const Position_unsigned &);

		Animal getWildAnimal() const;

		static const Area getArea(const std::string &);
		static unsigned int getHeight() { return k_height; }

	private:

		std::string m_name;
		// twoDimArray m_base;
		std::vector<std::string> m_base;
		portalMap m_portals;
		likelyhoodTuples m_likelyhoods;
		portalMap m_npcs;

};

#endif // _AREA_HPP
