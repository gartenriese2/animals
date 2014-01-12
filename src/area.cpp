#include "area.hpp"

#include <iostream>

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

Area::Area(const std::string & name, const twoDimArray & base, const portalMap & portals)
  : m_name(name),
  	m_base(base),
  	m_portals(portals)
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


twoDimArray Area::convertStringToTwoDimArr(const std::string & str) {

	twoDimArray arr;

	unsigned int count = 0;
	for (unsigned int i = 0; i < k_height; ++i) {
		for (int j = 0; j < k_width; ++j) {
			arr[i][j] = str[count++];
			if (str[count - 1] == '\n') {
				arr[i][j] = k_stopsign;
				break;
			}
		}
	}
	
	return arr;
}

portalMap Area::convertStringToPortalMap(const std::string & str) {

	portalMap map;
	
	unsigned int count = 0;
	
	while (count < str.size()) {
	
		std::string x;
		std::string y;
		std::string to;
		
		while (str[count++] != ',') x += str[count - 1];
		while (str[count++] != '>') y += str[count - 1];
		while (str[count++] != '\n') to += str[count - 1];
		Position p(std::stoi(x), std::stoi(y));
		map.emplace(p,to);

	}

	return map;

}

const Area Area::getArea(const std::string & s) {

	twoDimArray arr;
	portalMap map;
	try {
		arr = convertStringToTwoDimArr(m_reader.getBaseFromEntry(s));
		map = convertStringToPortalMap(m_reader.getPortalsFromEntry(s));
	} catch (char const * c) {
		std::cout << c << std::endl;
	}

	return Area(s, arr, map);

}
