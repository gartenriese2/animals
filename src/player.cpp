#include "player.hpp"

#include <random>
#include "tournament.hpp"

extern std::mt19937 generator;

static constexpr float k_grassEncounterProb = 0.15f;

Player::Player(Area area)
  : m_area(area),
  	m_position(18,9)
{
}

Player::~Player() {

}

void Player::printArea() const {

	m_area.print(m_position);

}

void Player::move(ArrowKey key) {

	switch(key) {
		case ArrowKey::UP:
			setPosition(m_position.x(), m_position.y() - 1);
			break;
		case ArrowKey::DOWN:
			setPosition(m_position.x(), m_position.y() + 1);
			break;
		case ArrowKey::LEFT:
			setPosition(m_position.x() - 1, m_position.y());
			break;
		case ArrowKey::RIGHT:
			setPosition(m_position.x() + 1, m_position.y());
			break;
		default:
			break;
	}

}

void Player::setPosition(unsigned int x, unsigned int y) {

	const twoDimArray base = m_area.getBase();

	if (x < base[0].size() && y < base.size() && base[y][x] != AreaType::BORDER) {
		m_position.set(x, y);
		switch (base[y][x]) {
			case AreaType::GRASS:
				grassAction();
				m_output = "\n";
				break;
			case AreaType::PORTAL:
				enterArea(m_area.getAreaFromPortalPos(m_position).getName());
				m_output = "\n";
				break;
			case AreaType::HEALING:
				m_output = m_party.heal();
				break;
			default:
				m_output = "\n";
				break;
		}
	} else {
		m_output = "\n";
	}

}

void Player::enterArea(const std::string & name) {

	std::string oldName = m_area.getName();
	m_area = Area::getArea(name);
	try {
		m_position = m_area.getPortalPos(oldName);
	} catch (char const * c) {
		std::cout << c << std::endl;
		m_area = Area::getArea(oldName);
	}

}

void Player::grassAction() {

	std::uniform_real_distribution<float> dist(0.f, 1.f);
	if (dist(generator) < k_grassEncounterProb) {
		Tournament t;
		Animal a = m_area.getWildAnimal();
		t.startSingleBattle(m_party.getFrontAnimal(), a);
	}

}
