#ifndef _NPCHAR_HPP
#define _NPCHAR_HPP

#include <string>

#include "position.hpp"
#include "console.hpp"
#include "party.hpp"

class NPChar {

	public:
		
		NPChar(const std::string &, const std::string &, const Position &, const Party &, const std::vector<std::string> &);
		~NPChar();

		bool wantsToBattle() const { return m_party.getSize() != 0; }
		void action(Party &);

		static const NPChar getNPC(const std::string &);

	protected:

		std::string m_name;
		std::string m_area;
		Position m_position;
		Party m_party;
		std::vector<std::string> m_text;

};

#endif // _NPC_HPP