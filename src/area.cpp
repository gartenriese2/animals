#include "area.hpp"

#include <iostream>

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

Area::Area(const std::string & name, const twoDimArr & base, const portalMap & portals)
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


Area & Area::getArea(const std::string & s) {

	if (Area::getAreas().count(s) == 0) {
		std::cout << "no such area: " << s << std::endl;
		abort();
	}

	return getAreas().at(s);

}

std::map<std::string, Area> & Area::getAreas() {
	
	static std::map<std::string, Area> s_areas {
		{	"Test",
			Area("Test",
				{{
				{"+++++++++"},
				{"+       +"},
				{"+       +"},
				{"+       +"},
				{"+       +"},
				{"+       o"},
				{"+       +"},
				{"+     ##+"},
				{"+     ##+"},
				{"+++++++++"}
				}},
				{{std::make_tuple(8,5), "Test2"}})			
		},
		{	"Test2",
			Area("Test2",
				{{
				{"+++++++++"},
				{"+   ####+"},
				{"+   ####+"},
				{"+   ####+"},
				{"+       +"},
				{"o       +"},
				{"+       +"},
				{"+       +"},
				{"+       +"},
				{"+++++++++"}
				}},
				{{std::make_tuple(0,5), "Test"}})			
		},
	};

	return s_areas;

}
