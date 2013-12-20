#include "attack.hpp"

Attack::Attack(const std::string & name, const Type & type, const unsigned int damage)
  : m_name(name), m_type(type), m_damage(damage)
{
}

Attack::~Attack() {
}
