#include "areadatabasereader.hpp"

#include "../gui/console.hpp"

#include <clocale>

AreaDatabaseReader::AreaDatabaseReader()
  : DatabaseReader("data/areas.database")
{
}

AreaDatabaseReader::~AreaDatabaseReader() {
}

const std::vector<std::string> AreaDatabaseReader::getBaseFromEntry(const std::string & str) {

	return getTagContentFromEntry('b', str);

}

const portalMap AreaDatabaseReader::getPortalMapFromEntry(const std::string & str) {

	return convertContentToPortalMap(getTagContentFromEntry('p', str));

}

const likelyhoodTuples AreaDatabaseReader::getLikelyhoodsFromEntry(const std::string & str) {

	return convertContentToLikelyhoodTuples(getTagContentFromEntry('l', str));

}

const portalMap AreaDatabaseReader::getNPCSFromEntry(const std::string & str) {

	return convertContentToNPCMap(getTagContentFromEntry('c', str));

}

const portalMap AreaDatabaseReader::convertContentToPortalMap(const std::vector<std::string> & content) {

	portalMap map;

	unsigned int count = 0;
	setlocale(LC_NUMERIC, "C");
	for (const auto & line : content) {

		count = 0;

		std::string x;
		std::string y;
		std::string to;
		while (line[count++] != ',') x += line[count - 1];
		while (line[count++] != '>') y += line[count - 1];
		while (count++ < line.size()) to += line[count - 1];
		Position_unsigned p(static_cast<unsigned int>(std::stoul(x)), static_cast<unsigned int>(std::stoul(y)));
		map.emplace(p,to);

	}
	setlocale(LC_NUMERIC, "");

	return map;

}

const likelyhoodTuples AreaDatabaseReader::convertContentToLikelyhoodTuples(const std::vector<std::string> & content) {

	likelyhoodTuples tup;

	unsigned int count = 0;
	setlocale(LC_NUMERIC, "C");
	for (const auto & line : content) {

		count = 0;

		std::string name;
		std::string a;
		std::string b;
		std::string prob;
		while (line[count++] != '>') name += line[count - 1];
		while (line[count++] != '-') a += line[count - 1];
		while (line[count++] != '>') b += line[count - 1];
		while (count++ < line.size()) prob += line[count - 1];
		tup.emplace_back(std::make_tuple(name, std::stoi(a), std::stoi(b), std::stof(prob)));

	}
	setlocale(LC_NUMERIC, "");

	return tup;

}

const portalMap AreaDatabaseReader::convertContentToNPCMap(const std::vector<std::string> & content) {

	portalMap map;

	unsigned int count = 0;
	setlocale(LC_NUMERIC, "C");
	for (const auto & line : content) {

		count = 0;

		std::string x;
		std::string y;
		std::string name;
		while (line[count++] != ',') x += line[count - 1];
		while (line[count++] != '>') y += line[count - 1];
		while (count++ < line.size()) name += line[count - 1];
		Position_unsigned p(static_cast<unsigned int>(std::stoul(x)), static_cast<unsigned int>(std::stoul(y)));
		map.emplace(p,name);

	}
	setlocale(LC_NUMERIC, "");

	return map;

}
