#include "npcdatabasereader.hpp"

#include "console.hpp"

NPCDatabaseReader::NPCDatabaseReader()
  : DatabaseReader("data/npcs.database")
{
}

NPCDatabaseReader::~NPCDatabaseReader() {
}

const partyTuples NPCDatabaseReader::getPartyTuplesFromEntry(const std::string & str) {
	
	std::vector<std::string> s = getTagContentFromEntry('p', str);
	if (s.empty()) return partyTuples();
	return convertContentToPartyTuples(s);

}

const locationTuple NPCDatabaseReader::getLocationFromEntry(const std::string & str) {

	return convertContentToLocationTuple(getTagContentFromEntry('l', str));

}

const std::vector<std::string> NPCDatabaseReader::getTextFromEntry(const std::string & str) {

	return getTagContentFromEntry('t', str);

}

const partyTuples NPCDatabaseReader::convertContentToPartyTuples(const std::vector<std::string> & content) {

	partyTuples tuples;

	unsigned int count = 0;
	setlocale(LC_NUMERIC, "C");
	for (const auto & line : content) {

		count = 0;

		std::string animal;
		std::string lvl;
		while (line[count++] != '>') animal += line[count - 1];
		while (count++ < line.size()) lvl += line[count - 1];
		tuples.emplace_back(animal,std::stoi(lvl));

	}
	setlocale(LC_NUMERIC, "");

	return tuples;

}

const locationTuple NPCDatabaseReader::convertContentToLocationTuple(const std::vector<std::string> & content) {

	locationTuple tup;

	unsigned int count = 0;
	
	std::string area;
	std::string x;
	std::string y;
	
	while (content[0][count++] != '>') area += content[0][count - 1];
	while (content[0][count++] != ',') x += content[0][count - 1];
	while (count++ < content[0].size()) y += content[0][count - 1];

	tup = std::make_tuple(area,Position(std::stoi(x),std::stoi(y)));

	return tup;

}
