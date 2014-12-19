#include "player.hpp"

#include <random>

#include "tournament.hpp"

#include "gui/areaconsole.hpp"
#include "gui/textconsole.hpp"
#include "gui/console.hpp"

extern std::mt19937 generator;

static constexpr float k_grassEncounterProb = 0.15f;

Player::Player(const locationTuple & spawn)
  : m_respawnPos(spawn)
{

	m_area = Area::getArea(std::get<0>(m_respawnPos));
	m_areaBase = std::make_shared<std::vector<std::string>>(m_area.getBase());
	m_position = std::make_shared<Position_unsigned>(std::get<1>(m_respawnPos));
	m_view = Position(0,1);

	AreaConsole::setAreaBase(m_areaBase);
	AreaConsole::setPosition(m_position);

}

Player::~Player() {
}

void Player::move(Key key) {

	switch(key) {
		case Key::UP:
			setPosition(m_position->x(), static_cast<unsigned int>(std::max(0, static_cast<int>(m_position->y()) - 1)));
			m_view = Position(0,-1);
			break;
		case Key::DOWN:
			setPosition(m_position->x(), m_position->y() + 1);
			m_view = Position(0,1);
			break;
		case Key::LEFT:
			setPosition(static_cast<unsigned int>(std::max(0, static_cast<int>(m_position->x()) - 1)), m_position->y());
			m_view = Position(-1,0);
			break;
		case Key::RIGHT:
			setPosition(m_position->x() + 1, m_position->y());
			m_view = Position(1,0);
			break;
		default:
			break;
	}

}

void Player::interact() {

	char c = m_area.getBase()[static_cast<unsigned int>(static_cast<int>(m_position->getY()) + m_view.getY())]
							 [static_cast<unsigned int>(static_cast<int>(m_position->getX()) + m_view.getX())];

	if (c == AreaType::NPC) {

		try {

			NPChar npc = m_area.getNPC(Position_unsigned(static_cast<unsigned int>(static_cast<int>(m_position->getX()) + m_view.getX()),
				static_cast<unsigned int>(static_cast<int>(m_position->getY()) + m_view.getY())));
			npc.action(m_party);
			if (!m_party.isHealthy()) {
				Console::clear();
				TextConsole::addText("You hurried back to a safe place to heal your animals!");
				TextConsole::print();
				TextConsole::emptyText();
				respawn();
			}

		} catch(char const * c) {
			DEB(c);
		}

	}

}

void Player::setPosition(unsigned int x, unsigned int y) {

	const std::vector<std::string> base = m_area.getBase();

	if (x < base[y].size() && y < base.size()
		&& base[y][x] != AreaType::BORDER
		&& base[y][x] != AreaType::NPC) {
		m_position->set(x, y);
		switch (base[y][x]) {
			case AreaType::GRASS:
				grassAction();
				break;
			case AreaType::PORTAL:
				enterArea(m_area.getAreaFromPortalPos(* m_position).getName());
				break;
			case AreaType::HEALING:
				m_party.heal();
				m_respawnPos = std::make_tuple(m_area.getName(), * m_position);
				break;
			default:
				break;
		}
	}

}

void Player::enterArea(const std::string & name) {

	std::string oldAreaName = m_area.getName();
	m_area = Area::getArea(name);

	try {

		* m_position = m_area.getPortalPos(oldAreaName);

	} catch (char const * c) {

		DEB(c);
		m_area = Area::getArea(oldAreaName);

	}

	* m_areaBase = m_area.getBase();

}

void Player::grassAction() {

	std::uniform_real_distribution<float> dist(0.f, 1.f);
	if (dist(generator) < k_grassEncounterProb) {
		Tournament t;

		AreaConsole::addText("You encounterd a wild animal!");
		AreaConsole::print();
		AreaConsole::emptyText();

		Animal a = m_area.getWildAnimal();
		t.startSingleBattle(m_party.getFrontAnimal(), a);
		if (!m_party.isHealthy()) {
			Console::clear();
			TextConsole::addText("You hurried back to a safe place to heal your animals!");
			TextConsole::print();
			TextConsole::emptyText();
			respawn();
		}
	}

}

void Player::respawn() {

	m_area = Area::getArea(std::get<0>(m_respawnPos));
	* m_areaBase = m_area.getBase();
	* m_position = std::get<1>(m_respawnPos);
	m_view = Position(0,1);

	m_party.heal();

}
