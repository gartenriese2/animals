#include "areadatabasereader.hpp"

#include <iostream>

AreaDatabaseReader::AreaDatabaseReader() {
	openFile();
}

AreaDatabaseReader::~AreaDatabaseReader() {
}

void AreaDatabaseReader::openFile() {

	m_file.open(k_filename);
	if (!m_file.good()) {
		std::cout << "Bad file!" << std::endl;
		abort();
	}

}

const std::string AreaDatabaseReader::nextEntry() {

	while (getNextTag() != Tag::NAME);
	return getNextWord();

}

const std::string AreaDatabaseReader::getBaseFromEntry(const std::string & str) {

	m_file.seekg(0);
	while (nextEntry() != str);
	while (getNextTag() != Tag::BASE);
	
	return getNextContent();

}

const std::string AreaDatabaseReader::getPortalsFromEntry(const std::string & str) {

	m_file.seekg(0);
	
	while (nextEntry() != str);
	while (getNextTag() != Tag::PORTALTAG);
	
	return getNextContent();

}
