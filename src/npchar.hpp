#ifndef _NPCHAR_HPP
#define _NPCHAR_HPP

#include <string>

#include "position.hpp"
#include "party.hpp"

class NPChar {

	public:

		NPChar(const std::string &, const std::string &, const Position_unsigned &, const Party &, const std::vector<std::string> &);
		~NPChar();

		bool wantsToBattle() const { return m_party.getSize() != 0; }
		void action(Party &);

		static const NPChar getNPC(const std::string &);

	protected:

		std::string m_name;
		std::string m_area;
		Position_unsigned m_position;
		Party m_party;
		std::vector<std::string> m_text;

};

#endif // _NPC_HPP
