#ifndef _ATTACK_H
#define _ATTACK_H

#include "type.hpp"

class Attack {
	
	public:
		
		Attack(const Type &, const unsigned int);
		~Attack();

		const unsigned int getDamage() const { return m_damage; }

	private:

		Type m_type;
		unsigned int m_damage;

	
};

#endif // _ATTACK_H