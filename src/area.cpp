#include "area.hpp"

#include <iostream>
#include <random>

extern std::mt19937 generator;
static AreaDatabaseReader m_reader;
static constexpr char k_stopsign = 'x';

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

Area::Area(const std::string & name, const twoDimArray & base, const portalMap & portals,
	const likelyhoodTuples & tuples)
  : m_name(name),
  	m_base(base),
  	m_portals(portals),
  	m_likelyhoods(tuples)
{
}

Area::~Area() {
}

void Area::print(const Position & pos) const {

	for (int i = 0; i < m_base.size(); ++i) {
		for (int j = 0; j < m_base[0].size() && m_base[i][j] != k_stopsign; ++j) {
			if (j == pos.getX() && i == pos.getY()) {
				std::cout << "P";
			} else {
				std::cout << m_base[i][j];
			}
		}
		std::cout << std::endl;
	}

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

	std::cout << "no portal at this position! " << pos << std::endl;
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


const Area Area::getArea(const std::string & s) {

	twoDimArray arr;
	portalMap map;
	likelyhoodTuples tuples;
	try {
		arr = m_reader.getBaseFromEntry(s);
		map = m_reader.getPortalMapFromEntry(s);
		tuples = m_reader.getLikelyhoodsFromEntry(s);
	} catch (char const * c) {
		std::cout << c << std::endl;
	}

	return Area(s, arr, map, tuples);

}
