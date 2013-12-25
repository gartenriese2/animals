#include "attackset.hpp"

AttackSet::AttackSet(const std::multimap<unsigned int, std::shared_ptr<Attack>> & set)
  : m_set(set)
{
}

AttackSet::~AttackSet() {
}