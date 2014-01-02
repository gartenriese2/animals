#include "player.hpp"

Player::Player(std::shared_ptr<Area> area)
  : m_area(area)
{
}

Player::~Player() {

}

void Player::move(ArrowKey key) {

	std::tuple<unsigned int, unsigned int> pos = m_area->getPlayerPos();
	switch(key) {
		case ArrowKey::UP:
			m_area->setPlayerPos(std::get<0>(pos), std::get<1>(pos) - 1);
			break;
		case ArrowKey::DOWN:
			m_area->setPlayerPos(std::get<0>(pos), std::get<1>(pos) + 1);
			break;
		case ArrowKey::LEFT:
			m_area->setPlayerPos(std::get<0>(pos) - 1, std::get<1>(pos));
			break;
		case ArrowKey::RIGHT:
			m_area->setPlayerPos(std::get<0>(pos) + 1, std::get<1>(pos));
			break;
		default:
			break;
	}

}
