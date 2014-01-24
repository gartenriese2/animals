#include "npcdatabasereader.hpp"

#include "console.hpp"

NPCDatabaseReader::NPCDatabaseReader() {
	openFile();
}

NPCDatabaseReader::~NPCDatabaseReader() {
}

void NPCDatabaseReader::openFile() {

	m_file.open(k_filename);
	if (!m_file.good()) {
		EXIT("Bad NPC database!");
	}

}

const partyTuples NPCDatabaseReader::getPartyTuplesFromEntry(const std::string & str) {
	
	std::string s = getTagContentFromEntry('p', str);
	if (s == "") return partyTuples();
	return convertStringToPartyTuples(s);

}

const locationTuple NPCDatabaseReader::getLocationFromEntry(const std::string & str) {

	return convertStringToLocationTuple(getTagContentFromEntry('l', str));

}

const std::string NPCDatabaseReader::getTextFromEntry(const std::string & str) {

	return getTagContentFromEntry('t', str);

}

const partyTuples NPCDatabaseReader::convertStringToPartyTuples(const std::string & str) {

	partyTuples tuples;
	
	unsigned int count = 0;
	
	while (count < str.size()) {
	
		std::string animal;
		std::string lvl;
		
		while (str[count++] != '>') animal += str[count - 1];
		while (str[count++] != '\n') lvl += str[count - 1];
		tuples.emplace_back(animal,std::stoi(lvl));

	}

	return tuples;

}

const locationTuple NPCDatabaseReader::convertStringToLocationTuple(const std::string & str) {

	locationTuple tup;

	unsigned int count = 0;
	
	std::string area;
	std::string x;
	std::string y;
	
	while (str[count++] != '>') area += str[count - 1];
	while (str[count++] != ',') x += str[count - 1];
	while (str[count++] != '\n') y += str[count - 1];

	tup = std::make_tuple(area,Position(std::stoi(x),std::stoi(y)));

	return tup;

}
