#include "attack.hpp"

#include "gui/console.hpp"
#include "database/attackdatabasereader.hpp"

static AttackDatabaseReader m_reader;

Attack::Attack(const std::string & name, const AttackStats & stats)
  : m_name(name), m_stats(stats)
{
}

Attack::~Attack() {
}

const std::shared_ptr<Attack> Attack::getAttack(const std::string & s) {

	Type type;
	std::unordered_map<std::string, double> map;

	try {
		type = m_reader.getTypeFromEntry(s);
		map = m_reader.getMapFromEntry(s);
	} catch (char const * c) {
		DEB(c);
	}

	AttackStats as(type, map);

	return std::make_shared<Attack>(Attack(s, as));

}
