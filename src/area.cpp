#include "area.hpp"

#include <random>

#include "console.hpp"

extern std::mt19937 generator;
static AreaDatabaseReader m_reader;

Area::Area()
  : m_name("default")
{

	m_base = {{
		{"+++++++++"},
		{"+       +"},
		{"+       +"},
		{"+       +"},
		{"+       +"},
		{"+       +"},
		{"+       +"},
		{"+       +"},
		{"+       +"},
		{"+++++++++"}
	}};

}

// Area::Area(const std::string & name, const twoDimArray & base, const portalMap & portals,
// 	const likelyhoodTuples & tuples, const portalMap & npcs)
//   : m_name(name),
//   	m_base(base),
//   	m_portals(portals),
//   	m_likelyhoods(tuples),
//   	m_npcs(npcs)
// {
// }

Area::Area(const std::string & name, const std::vector<std::string> & base, const portalMap & portals,
	const likelyhoodTuples & tuples, const portalMap & npcs)
  : m_name(name),
  	m_base(base),
  	m_portals(portals),
  	m_likelyhoods(tuples),
  	m_npcs(npcs)
{
}

Area::~Area() {
}

const Position & Area::getPortalPos(const std::string & name) const {

	for (const auto & i : m_portals) {
		if (name == i.second) {
			return i.first;
		}
	}

	throw "Missing portal!";

}

const Area Area::getAreaFromPortalPos(const Position & pos) {

	for (const auto & i : m_portals) {
		if (pos == i.first) {
			return getArea(i.second);
		}
	}

	DEB("no portal at this position! (" + std::to_string(pos.getX()) + "|" + std::to_string(pos.getY()) + ")" );
	return * this;

}

Animal Area::getWildAnimal() const {

	float probSum = 0.f;
	for (auto i : m_likelyhoods) {
		probSum += std::get<3>(i);
	}
	std::uniform_real_distribution<float> dist(0.f, probSum);

	float choice = dist(generator);
	probSum = 0.f;
	unsigned int i = 0;
	for (i = 0; i < m_likelyhoods.size(); ++i) {
		probSum += std::get<3>(m_likelyhoods[i]);
		if (choice < probSum) break;
	}

	Animal animal = Animal::getAnimal(std::get<0>(m_likelyhoods[i]));
	std::uniform_int_distribution<int> dist2(std::get<1>(m_likelyhoods[i]), std::get<2>(m_likelyhoods[i]));
	animal.raiseLevels(dist2(generator) - 1);
	
	return animal;

}

const NPChar Area::getNPC(const Position & pos) {

	for (const auto & i : m_npcs) {
		if (pos == i.first) {
			return NPChar::getNPC(i.second);
		}
	}

	EXIT("no npc at this position! (" + std::to_string(pos.getX()) + "|" + std::to_string(pos.getY()) + ")");
	abort();

}


const Area Area::getArea(const std::string & s) {

	// twoDimArray arr;
	std::vector<std::string> arr;
	portalMap map;
	likelyhoodTuples tuples;
	portalMap npcs;

	try {
		arr = m_reader.getBaseFromEntry(s);
		map = m_reader.getPortalMapFromEntry(s);
		tuples = m_reader.getLikelyhoodsFromEntry(s);
		npcs = m_reader.getNPCSFromEntry(s);
	} catch (char const * c) {
		DEB(c);
	}

	return Area(s, arr, map, tuples, npcs);

}
