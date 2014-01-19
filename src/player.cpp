#include "player.hpp"

#include <random>
#include "tournament.hpp"
#include "console.hpp"
#include "io.hpp"

extern std::mt19937 generator;

static constexpr float k_grassEncounterProb = 0.15f;

Player::Player(const std::tuple<std::string,Position> & spawn)
  : m_respawnPos(spawn)
{
	m_area = Area::getArea(std::get<0>(m_respawnPos));
	Console::setAreaBase(m_area.getBase());
	m_position = std::get<1>(m_respawnPos);
	Console::setPosition(m_position);
	m_view = Position(0,1);
}

Player::~Player() {

}

void Player::printArea() const {

	Console::printArea();

}

void Player::move(Key key) {

	switch(key) {
		case Key::UP:
			setPosition(m_position.x(), m_position.y() - 1);
			m_view = Position(0,-1);
			break;
		case Key::DOWN:
			setPosition(m_position.x(), m_position.y() + 1);
			m_view = Position(0,+1);
			break;
		case Key::LEFT:
			setPosition(m_position.x() - 1, m_position.y());
			m_view = Position(-1,0);
			break;
		case Key::RIGHT:
			setPosition(m_position.x() + 1, m_position.y());
			m_view = Position(1,0);
			break;
		default:
			break;
	}

	Console::setPosition(m_position);

}

void Player::interact() {

	char c = m_area.getBase()[m_position.getY() + m_view.getY()][m_position.getX() + m_view.getX()];
	
	if (c == AreaType::NPC) {
		
		try {
			
			NPChar npc = m_area.getNPC(Position(m_position.getX() + m_view.getX(),m_position.getY() + m_view.getY()));
			npc.action(m_party);
			if (!m_party.isHealthy()) {
				Console::clearArea();
				Console::addText("You hurried back to a safe place to heal your animals!");
				Console::printText();
				IO::emptyOutput();
				respawn();
			}

		} catch(char const * c) {
			DEB(c);
		}

	}

}

void Player::setPosition(unsigned int x, unsigned int y) {

	const twoDimArray base = m_area.getBase();

	if (x < base[0].size() && y < base.size()
		&& base[y][x] != AreaType::BORDER
		&& base[y][x] != AreaType::NPC) {
		m_position.set(x, y);
		switch (base[y][x]) {
			case AreaType::GRASS:
				grassAction();
				break;
			case AreaType::PORTAL:
				enterArea(m_area.getAreaFromPortalPos(m_position).getName());
				break;
			case AreaType::HEALING:
				m_party.heal();
				m_respawnPos = std::make_tuple(m_area.getName(),m_position);
				break;
			default:
				break;
		}
	}

}

void Player::enterArea(const std::string & name) {

	std::string oldName = m_area.getName();
	m_area = Area::getArea(name);
	try {
		m_position = m_area.getPortalPos(oldName);
	} catch (char const * c) {
		DEB(c);
		m_area = Area::getArea(oldName);
	}
	Console::setAreaBase(m_area.getBase());
	Console::setPosition(m_position);

}

void Player::grassAction() {

	std::uniform_real_distribution<float> dist(0.f, 1.f);
	if (dist(generator) < k_grassEncounterProb) {
		Tournament t;
		Console::clearArea();
		Console::addText("You encounterd a wild animal!");
		Console::printText();
		IO::emptyOutput();

		Animal a = m_area.getWildAnimal();
		t.startSingleBattle(m_party.getFrontAnimal(), a);
		if (!m_party.isHealthy()) {
			Console::clearArea();
			Console::addText("You hurried back to a safe place to heal your animals!");
			Console::printText();
			IO::emptyOutput();
			respawn();
		}
	}

}

void Player::respawn() {

	m_area = Area::getArea(std::get<0>(m_respawnPos));
	Console::setAreaBase(m_area.getBase());
	m_position = std::get<1>(m_respawnPos);
	Console::setPosition(m_position);
	m_view = Position(0,1);
	m_party.heal();

}
