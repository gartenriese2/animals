#include "attackdatabasereader.hpp"

#include "console.hpp"

#include <clocale>

AttackDatabaseReader::AttackDatabaseReader() {
	openFile();
}

AttackDatabaseReader::~AttackDatabaseReader() {
}

void AttackDatabaseReader::openFile() {

	m_file.open(k_filename);
	if (!m_file.good()) {
		EXIT("Bad Attack database!");
	}

}

const Type AttackDatabaseReader::getTypeFromEntry(const std::string & str) {

	std::string content = getTagContentFromEntry('t', str);
	return convertStringToType(content);

}

const std::unordered_map<std::string, double> AttackDatabaseReader::getMapFromEntry(const std::string & str) {

	std::string content = getTagContentFromEntry('b', str);
	return convertStringToMap(content);

}

const Type AttackDatabaseReader::convertStringToType(const std::string & str) {

	std::string type;
	unsigned int count = 0;
	while(str[count] != '\n') type += str[count++];

	return Type(Database::getBaseTypeFromString(type));

}

const std::unordered_map<std::string, double> AttackDatabaseReader::convertStringToMap(const std::string & str) {

	std::unordered_map<std::string, double> map;

	unsigned int count = 0;
	setlocale(LC_NUMERIC, "C");
	while (count < str.size()) {
	
		std::string entry;
		std::string value;
		
		while (str[count++] != ' ') entry += str[count - 1];
		while (str[count++] != '\n') value += str[count - 1];
		map.emplace(entry,std::stod(value));

	}
	setlocale(LC_NUMERIC, "");

	return map;

}
