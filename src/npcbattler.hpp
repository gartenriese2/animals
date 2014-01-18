#ifndef _NPCBATTLER_HPP
#define _NPCBATTLER_HPP

#include "npc.hpp"
#include "party.hpp"

class NPCBattler : public NPC {

	public:

		NPCBattler(const std::string &, const std::string &, const Position &, const Party &);
		~NPCBattler();

		bool wantsToBattle() const { return true; }

	private:

		Party m_party;

};

#endif // _NPCBATTLER_HPP