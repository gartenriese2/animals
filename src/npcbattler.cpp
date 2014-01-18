#include "npcbattler.hpp"

NPCBattler::NPCBattler(const std::string & name, const std::string & area, const Position & pos, const Party & party)
  : NPC(name, area, pos),
  	m_party(party)
{
}