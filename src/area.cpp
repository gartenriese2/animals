#include "area.hpp"

#include <iostream>

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

Area::Area(const std::string & name, const twoDimArray & base, const portalMap & portals)
  : m_name(name),
  	m_base(base),
  	m_portals(portals)
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

	std::cout << "no portal to area " << getName() << " from area " << name << std::endl;
	abort();

}

const Area & Area::getAreaFromPortalPos(const Position & pos) {

	for (const auto & i : m_portals) {
		if (pos == i.first) {
			return getArea(i.second);
		}
	}

	std::cout << "no portal at this position! (" << pos << std::endl;
	return * this;

}

twoDimArray Area::convertStringToTwoDimArr(const std::string & str) const {

	twoDimArray arr;
	for (unsigned int i = 0; i < k_height; ++i) {
		for (int j = 0; j < k_width && str[i * k_width + j] != '\n'; ++j) {
			arr[i][j] = str[i * k_width + j];
		}
	}
	return arr;

}


Area & Area::getArea(const std::string & s) {

	// if (Area::getAreas().count(s) == 0) {
	// 	std::cout << "no such area: " << s << std::endl;
	// 	abort();
	// }

	// return getAreas().at(s);

	m_reader.getBaseFromEntry(s);

}

std::map<std::string, Area> & Area::getAreas() {
	
	static std::map<std::string, Area> s_areas {
		{	"Test",
			Area("Test",
				{{
				{"++++++++++"},
				{"+        +"},
				{"+        +"},
				{"+        +"},
				{"+        +"},
				{"+       o+"},
				{"+        +"},
				{"+     ###+"},
				{"+     ###+"},
				{"++++++++++"}
				}},
				{{Position(8,5), "Test2"}})
		},
		{	"Test2",
			Area("Test2",
				{{
				{"+++++++++"},
				{"+   ####+"},
				{"+   ####+"},
				{"+   ####+"},
				{"+       +"},
				{"+o     o+"},
				{"+       +"},
				{"+       +"},
				{"+      H+"},
				{"+++++++++"}
				}},
				{{Position(1,5), "Test"},
				 {Position(7,5), "Beach1"}})
		},
		{	"Beach1",
			Area("Beach1",
				{{
				{"+++++++++++++"},
				{"+       ~~~~+"},
				{"+       ~~~~+"},
				{"+       ~~~~+"},
				{"+       ~~~~+"},
				{"+o      ~~~o+"},
				{"+       ~~~~+"},
				{"+       ~~~~+"},
				{"+       ~~~~+"},
				{"+++++++++++++"}
				}},
				{{Position(1,5), "Test2"},
				 {Position(11,5), "Water1"}})
		},
		{	"Water1",
			Area("Water1",
				{{
				{"+++++++++++++++++++++++++++"},
				{"+~~~~~~~~~~~~~~~~~~~~~~~~~+"},
				{"+~~~~~~~~~~~~~~~~~~~~~~~~~+"},
				{"+~~~~~~~~~~~~~~~~~~~~~~~~~+"},
				{"+~~~~~~~~~~~~~~~~~~~~~~~~~+"},
				{"+o~~~~~~~~~~~~~~~~~~~~~~~~+"},
				{"+~~~~~~~~~~~~~~~~~~~~~~~~~+"},
				{"+~~~~~~~~~~~~~~~~~~~~~~~~~+"},
				{"+~~~~~~~~~~~~~~~~~~~~~~~~~+"},
				{"+++++++++++++++++++++++++++"}
				}},
				{{Position(1,5), "Beach1"}})
		},
	};

	return s_areas;

}
