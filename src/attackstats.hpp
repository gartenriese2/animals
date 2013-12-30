#ifndef _ATTACKSTATS_HPP
#define _ATTACKSTATS_HPP

#include "type.hpp"

class AttackStats {

	public:

		AttackStats(const Type &, int,
			int odmg = 0, float fam = 1.f, float fdm = 1.f, float fsm = 1.f,
			float oam = 1.f, float odm = 1.f, float osm = 1.f, float p = 1.f);
		~AttackStats();

		const Type & getType() const { return m_type; }
		const int getFoeDamage() const { return m_foeDamage; }
		const int getOwnDamage() const { return m_ownDamage; }

		const float getFoeAttackModifier() const { return m_foeAttackModifier; }
		const float getFoeDefenseModifier() const { return m_foeDefenseModifier; }
		const float getFoeSpeedModifier() const { return m_foeSpeedModifier; }
		const float getOwnAttackModifier() const { return m_ownAttackModifier; }
		const float getOwnDefenseModifier() const { return m_ownDefenseModifier; }
		const float getOwnSpeedModifier() const { return m_ownSpeedModifier; }

		const float getProbability() const { return m_probability; }

	private:

		Type m_type;

		int m_foeDamage;
		int m_ownDamage;

		float m_foeAttackModifier;
		float m_foeDefenseModifier;
		float m_foeSpeedModifier;

		float m_ownAttackModifier;
		float m_ownDefenseModifier;
		float m_ownSpeedModifier;

		float m_probability;

};

#endif // _ATTACKSTATS_HPP