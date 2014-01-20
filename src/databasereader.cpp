#include "databasereader.hpp"

#include <iostream>
#include "typedefs.hpp"

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

const char DatabaseReader::getNextTag() {

	char c;
	while (m_file.good() && (c = m_file.get()) != '<') goToNextLine();
	
	c = m_file.get();
	goToNextLine();
//debugOutput(c);
	if (c == 'n' || c == 'b' || c == 'p' || c == 'l' || c == 'c' || c == 't' || c == 'e') return c;
	throw "Unknown tag!";

}

const std::string DatabaseReader::nextEntry() {

	char c;
	while ((c = getNextTag()) != 'n' && c != 'e');
	if (c == 'e') return "";
	return getNextWord();

}

const std::string DatabaseReader::getNextWord() {

	std::string word;
	std::getline(m_file,word);
	return word;

}

const std::string DatabaseReader::getNextContent() {

	std::string base;
	std::string tmp;

	while ((tmp = getNextWord())[0] != '<' && tmp[0] != '/') {
		base += tmp + '\n';
	}
	return base;

}

const std::string DatabaseReader::getTagContentFromEntry(const char & tag, const std::string & str) {

	m_file.seekg(0);
	std::string s;
	char c;
	while ((s = nextEntry()) != str) {}

	while ((c = getNextTag()) != tag) {
		if (c == 'n' || c == 'e') return "";
	}
	return getNextContent();

}
