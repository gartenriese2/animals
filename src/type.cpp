#include "type.hpp"

Type::Type(const BaseType t1, const BaseType t2) {

	m_types.emplace_back(t1);
	if (t2 != BaseType::None) m_types.emplace_back(t2);

}

Type::~Type() {

}

const std::vector<BaseType> & Type::getBaseTypes() const {

	return m_types;

}

const std::string Type::getString() const {

	std::string s;
	for (const auto & i : m_types) {
		s.append(Database::getStringFromBaseType(i));
	}
	return s;

}

const float Type::getEffectValueAgainst(const Type & against) const {

	float f = 1.f;

	for (const auto & i : m_types) {
		for (const auto & j : against.getBaseTypes()) {
			f *= Database::getEffectivenessValue(Database::getEffectiveness(i, j));
		}
	}

	return f;

}

const EffectiveType Type::getEffectTypeAgainst(const Type & against) const {

	float f = getEffectValueAgainst(against);

	if (f == Database::getEffectivenessValue(EffectiveType::Zero)) {
		return EffectiveType::Zero;
	}
	if (f <= Database::getEffectivenessValue(EffectiveType::HighlyIneffective)) {
		return EffectiveType::HighlyIneffective;
	}
	if (f <= Database::getEffectivenessValue(EffectiveType::Ineffective)) {
		return EffectiveType::Ineffective;
	}
	if (f <= Database::getEffectivenessValue(EffectiveType::SlightlyIneffective)) {
		return EffectiveType::SlightlyIneffective;
	}
	if (f < Database::getEffectivenessValue(EffectiveType::SlightlyEffective)) {
		return EffectiveType::Neutral;
	}
	if (f < Database::getEffectivenessValue(EffectiveType::Effective)) {
		return EffectiveType::SlightlyEffective;
	}
	if (f < Database::getEffectivenessValue(EffectiveType::HighlyEffective)) {
		return EffectiveType::Effective;
	}
	if (f < Database::getEffectivenessValue(EffectiveType::MostEffective)) {
		return EffectiveType::HighlyEffective;
	}
	return EffectiveType::MostEffective;

}

const std::string Type::getEffectStringAgainst(const Type & against) const {

	return Database::getStringFromEffectivenessType(getEffectTypeAgainst(against));

}

std::ostream & operator<<(std::ostream & os, Type type) {
  
  os << type.getString();
  return os;

}
