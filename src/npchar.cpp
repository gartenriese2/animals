#include "npchar.hpp"

#include "npcdatabasereader.hpp"
#include "console.hpp"
#include "party.hpp"
#include "io.hpp"
#include "tournament.hpp"

static NPCDatabaseReader m_reader;

NPChar::NPChar(const std::string & name, const std::string & area, const Position & pos, const Party & party, const std::string & text)
  : m_name(name),
  	m_area(area),
  	m_position(pos),
  	m_party(party),
  	m_text(text)
{
}

NPChar::~NPChar() {
}

void NPChar::action(Party & party) {

	unsigned int count = 0;
	
	while(count < m_text.size()) {
		std::string tmp;
		
		while(m_text[count] != '\n' && count < m_text.size()) {
			tmp += m_text[count++];
		}
		++count;
		
		Console::addText(m_name + ": " + tmp);
		
	}

	Console::printText();
	IO::emptyOutput();
	
	if (wantsToBattle()) {
		Console::addText(m_name + " wants to battle!");
		Console::printText();
		IO::emptyOutput();
		Console::clearArea();
		Tournament t;
		t.startTrainerBattles(party, m_party);
	}
}


const NPChar NPChar::getNPC(const std::string & s) {

	partyTuples vec;
	locationTuple tuple;
	std::string str;

	try {
		vec = m_reader.getPartyTuplesFromEntry(s);
		tuple = m_reader.getLocationFromEntry(s);
		str = m_reader.getTextFromEntry(s);
	} catch (char const * c) {
		DEB(c);
		abort();
	}

	Party p;
	for (const auto & t : vec) {
		p.addAnimal(std::get<0>(t));
	}
	for (unsigned int i = 0; i < p.getSize(); ++i) {
		p.getAnimal(i).raiseLevels(std::get<1>(vec[i]) - 1);
	}
	return NPChar(s, std::get<0>(tuple), std::get<1>(tuple), p, str);

}
