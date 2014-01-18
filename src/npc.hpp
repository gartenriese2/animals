#ifndef _NPC_HPP
#define _NPC_HPP

#include <string>

#include "position.hpp"

class NPC {

	public:
		
		NPC(const std::string &, const std::string &, const Position &);
		~NPC();

		virtual bool wantsToBattle() const { return false; }

	protected:

		std::string m_name;
		std::string m_area;
		Position m_position;

};

#endif // _NPC_HPP