#ifndef _ATTACKSTATS_HPP
#define _ATTACKSTATS_HPP

#include "type.hpp"
#include <unordered_map>

class Data {
public:
	Data(const Type & t) { m_type = t; }
	Data(int i) { m_int = i; }
	Data(float f) { m_float = f; }
	Type getType() const { return m_type; }
	int getInt() const { return m_int; }
	float getFloat() const { return m_float; }
private:
	Type m_type;
	int m_int;
	float m_float;
};

class AttackStats {

	public:

		AttackStats(const Type &, int, int odmg = 0, float p = 1.f,
			float fam = 1.f, float fdm = 1.f, float fsm = 1.f,
			float oam = 1.f, float odm = 1.f, float osm = 1.f,
			float ohm = 0.f);
		AttackStats(const std::unordered_map<std::string, Data> &);
		AttackStats(const Type &, int, float);
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
		const float getOwnHealthModifier() const { return m_ownHealthModifier; }

		const float getProbability() const { return m_probability; }

	private:

		Type m_type;

		int m_foeDamage;
		int m_ownDamage;

		float m_probability;

		float m_foeAttackModifier;
		float m_foeDefenseModifier;
		float m_foeSpeedModifier;

		float m_ownAttackModifier;
		float m_ownDefenseModifier;
		float m_ownSpeedModifier;
		float m_ownHealthModifier;

		

};



#endif // _ATTACKSTATS_HPP