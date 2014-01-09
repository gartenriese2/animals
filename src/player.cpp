#include "player.hpp"

#include <random>
#include "tournament.hpp"

extern std::mt19937 generator;

static constexpr float k_grassEncounterProb = 0.15f;

Player::Player(Area & area)
  : m_area(area),
  	m_position(1,1)
{
}

Player::~Player() {

}

void Player::printArea() const {

	const twoDimArr base = m_area.getBase();

	for (unsigned int i = 0; i < base.size(); ++i) {

		for (unsigned int j = 0; j < base[i].size(); ++j) {
			
			if (j == m_position.getX() && i == m_position.getY()) {
				std::cout << "P";
			} else {
				std::cout << base[i][j];
			}
			
		}

		std::cout << std::endl;

	}

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

	const twoDimArr base = m_area.getBase();

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
	m_position = m_area.getPortalPos(oldName);

}

void Player::grassAction() {

	std::uniform_real_distribution<float> dist(0.f, 1.f);
	if (dist(generator) < k_grassEncounterProb) {
		Tournament t;
		t.startSingleRandomBattle(m_party.getFrontAnimal());
	}

}
