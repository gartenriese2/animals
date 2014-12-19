#include "attackdatabasereader.hpp"

#include "gui/console.hpp"

#include <clocale>

AttackDatabaseReader::AttackDatabaseReader()
  : DatabaseReader("data/attacks.database")
{
}

AttackDatabaseReader::~AttackDatabaseReader() {
}

const Type AttackDatabaseReader::getTypeFromEntry(const std::string & str) {

	return convertContentToType(getTagContentFromEntry('t', str));

}

const std::unordered_map<std::string, double> AttackDatabaseReader::getMapFromEntry(const std::string & str) {

	return convertContentToMap(getTagContentFromEntry('b', str));

}

const Type AttackDatabaseReader::convertContentToType(const std::vector<std::string> & content) {

	return Type(Database::getBaseTypeFromString(content[0]));

}

const std::unordered_map<std::string, double> AttackDatabaseReader::convertContentToMap(const std::vector<std::string> & content) {

	std::unordered_map<std::string, double> map;

	unsigned int count = 0;
	setlocale(LC_NUMERIC, "C");
	for (const auto & line : content) {

		count = 0;

		std::string entry;
		std::string value;
		while (line[count++] != ' ') entry += line[count - 1];
		while (count++ < line.size()) value += line[count - 1];
		map.emplace(entry,std::stod(value));

	}
	setlocale(LC_NUMERIC, "");

	return map;

}
