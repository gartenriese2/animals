#include "databasereader.hpp"

#include <iostream>

DatabaseReader::DatabaseReader() {

}

DatabaseReader::~DatabaseReader() {

}

void DatabaseReader::goToNextLine() {
	char c;
	do {
		while (m_file.good() && (c = m_file.get()) != '\n') {}
	} while (c == '/');
}

Tag DatabaseReader::getNextTag() {

	char c;
	while (m_file.good() && (c = m_file.get()) != '<') goToNextLine();
	
	switch (c = m_file.get()) {
		case 'n':
			goToNextLine();
			return Tag::NAME;
		case 'b':
			goToNextLine();
			return Tag::BASE;
		case 'p':
			goToNextLine();
			return Tag::PORTALTAG;
		case 'l':
			goToNextLine();
			return Tag::LIKELYHOODS;
		case 'e':
			throw "End of database!";
		default:
			throw "Unknown tag!";
	}

}

const std::string DatabaseReader::getNextWord() {

	std::string word;
	std::getline(m_file,word);

	return word;

}

const std::string DatabaseReader::getNextContent() {

	std::string base;
	std::string tmp;

	while ((tmp = getNextWord())[0] != '<') {
		base += tmp + '\n';
	}
	
	return base;

}

const std::string DatabaseReader::getTagContentFromEntry(const Tag & tag, const std::string & str) {

	m_file.seekg(0);

	while (nextEntry() != str);
	while (getNextTag() != tag);

	return getNextContent();

}
