#include "npchar.hpp"

#include "gui/areaconsole.hpp"
#include "gui/console.hpp"
#include "gui/io.hpp"

#include "database/npcdatabasereader.hpp"
#include "party.hpp"
#include "tournament.hpp"

static NPCDatabaseReader m_reader;

NPChar::NPChar(const std::string & name, const std::string & area, const Position_unsigned & pos, const Party & party, const std::vector<std::string> & text)
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

	// unsigned int count = 0;

	// while(count < m_text.size()) {
	// 	std::string tmp;

	// 	while(m_text[count] != '\n' && count < m_text.size()) {
	// 		tmp += m_text[count++];
	// 	}
	// 	++count;

	// 	AreaConsole::addText(m_name + ": " + tmp);

	// }

	AreaConsole::addText(m_text);

	AreaConsole::print();
	AreaConsole::emptyText();

	if (wantsToBattle()) {
		AreaConsole::addText(m_name + " wants to battle!");
		AreaConsole::print();
		AreaConsole::emptyText();
		// AreaConsole::clearArea();
		Tournament t;
		t.startTrainerBattles(party, m_party);
	}
}


const NPChar NPChar::getNPC(const std::string & s) {

	partyTuples vec;
	locationTuple tuple;
	// std::string str;
	std::vector<std::string> str;

	try {
		vec = m_reader.getPartyTuplesFromEntry(s);
		tuple = m_reader.getLocationFromEntry(s);
		str = m_reader.getTextFromEntry(s);
	} catch (char const * c) {
		EXIT(c);
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
