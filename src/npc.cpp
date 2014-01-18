#include "npc.hpp"

NPC::NPC(const std::string & name, const std::string & area, const Position & pos)
  : m_name(name),
  	m_area(area),
  	m_position(pos)
{
}

NPC::~NPC() {

}
