#ifndef _ATTACK_H
#define _ATTACK_H

#include "type.hpp"

class Attack {
	
	public:
		
		Attack(const std::string &, const Type &, const unsigned int);
		~Attack();

		const unsigned int getDamage() const { return m_damage; }
		const std::string getName() const { return m_name; }
		const Type & getType() const { return m_type; }

	private:

		std::string m_name;
		Type m_type;
		unsigned int m_damage;

	
};

#endif // _ATTACK_H