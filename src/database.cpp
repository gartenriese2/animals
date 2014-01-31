#include "database.hpp"


static constexpr float k_Zero = 0.f;
static constexpr float k_HighlyIneffective = 0.25f;
static constexpr float k_Ineffective = 0.5f;
static constexpr float k_SlightlyIneffective = 0.75f;
static constexpr float k_Neutral = 1.f;
static constexpr float k_SlightlyEffective = 1.25f;
static constexpr float k_Effective = 1.5f;
static constexpr float k_HighlyEffective = 2.f;
static constexpr float k_MostEffective = 2.5f;


static std::vector<float> k_Fire {			1.00f, 0.25f, 2.50f, 1.50f, 1.00f, 0.50f, 0.25f, 1.00f, 2.50f, 1.00f, 1.00f, 1.00f,
										       	   2.00f, 1.00f, 1.50f, 0.75f, 0.00f, 1.00f, 1.00f, 1.00f, 1.00f, 0.50f, 1.50f, 0.50f};

static std::vector<float> k_Water {			2.50f, 1.00f, 1.00f, 1.25f, 0.50f, 1.25f, 1.50f, 1.00f, 0.50f, 1.00f, 1.00f, 1.00f,
										   	   	   0.25f, 1.00f, 1.00f, 1.00f, 2.50f, 1.00f, 1.50f, 1.25f, 1.00f, 0.50f, 1.50f, 0.50f};

static std::vector<float> k_Ice {			1.00f, 1.25f, 0.75f, 1.00f, 0.50f, 1.25f, 1.00f, 1.50f, 1.50f, 1.25f, 1.00f, 1.00f,
										       	   1.00f, 1.00f, 1.00f, 1.00f, 0.50f, 1.00f, 0.75f, 1.00f, 1.25f, 2.00f, 1.50f, 1.00f};

static std::vector<float> k_Snow {			1.00f, 1.00f, 0.00f, 0.75f, 1.00f, 1.00f, 1.25f, 2.00f, 1.25f, 1.00f, 1.25f, 1.00f,
										       	   0.75f, 1.00f, 1.25f, 1.00f, 0.50f, 0.75f, 0.75f, 1.00f, 1.25f, 1.25f, 1.50f, 1.25f};

static std::vector<float> k_Electro {		1.00f, 2.50f, 1.00f, 1.25f, 0.50f, 0.25f, 0.00f, 0.75f, 0.00f, 1.00f, 1.50f, 1.00f,
										       	   2.00f, 1.00f, 1.00f, 1.00f, 1.00f, 1.50f, 0.25f, 1.00f, 1.00f, 1.00f, 1.50f, 2.00f};

static std::vector<float> k_Stone {			1.00f, 0.50f, 2.00f, 0.75f, 2.00f, 1.25f, 1.00f, 0.75f, 1.50f, 1.00f, 0.25f, 1.00f,
										       	   0.75f, 1.50f, 1.00f, 1.50f, 0.75f, 1.00f, 0.75f, 1.00f, 1.00f, 0.75f, 1.00f, 1.25f};

static std::vector<float> k_Earth {			2.00f, 0.75f, 1.25f, 1.00f, 1.50f, 0.75f, 1.00f, 0.75f, 1.00f, 1.00f, 0.50f, 1.00f,
										       	   1.50f, 1.00f, 1.00f, 1.50f, 0.75f, 1.00f, 1.00f, 1.00f, 0.75f, 1.00f, 1.00f, 1.00f};

static std::vector<float> k_Air {			0.75f, 1.00f, 0.50f, 0.75f, 1.00f, 0.50f, 1.25f, 1.50f, 1.00f, 1.00f, 1.00f, 1.00f,
										       	   0.00f, 2.00f, 1.00f, 1.00f, 1.50f, 1.00f, 0.25f, 1.00f, 0.75f, 2.00f, 1.00f, 1.00f};

static std::vector<float> k_Plant {			0.25f, 2.00f, 0.75f, 0.75f, 2.00f, 2.00f, 2.00f, 1.00f, 1.00f, 1.00f, 0.75f, 1.25f,
										       	   0.25f, 1.00f, 1.00f, 2.50f, 0.25f, 1.00f, 1.00f, 1.25f, 0.75f, 0.75f, 2.00f, 1.00f};

static std::vector<float> k_Normal {		1.00f, 1.00f, 1.00f, 1.00f, 1.00f, 0.25f, 1.00f, 1.00f, 1.00f, 1.00f, 0.00f, 1.00f,
										   	   	   0.25f, 1.00f, 1.00f, 1.00f, 1.00f, 0.75f, 1.00f, 0.75f, 0.75f, 2.00f, 1.00f, 2.50f};

static std::vector<float> k_Ghost {			1.00f, 1.00f, 1.00f, 1.00f, 1.00f, 1.50f, 1.25f, 1.00f, 1.00f, 1.50f, 0.00f, 0.00f,
										   	   	   1.50f, 1.50f, 1.00f, 1.25f, 1.00f, 0.75f, 1.00f, 1.50f, 2.00f, 0.50f, 0.00f, 1.25f};

static std::vector<float> k_Psycho {		1.00f, 1.00f, 1.00f, 1.00f, 1.00f, 1.00f, 1.00f, 1.00f, 1.00f, 2.00f, 2.50f, 1.00f,
										   	   	   1.00f, 2.00f, 1.25f, 1.25f, 1.00f, 2.00f, 1.00f, 1.00f, 1.00f, 0.25f, 0.00f, 2.00f};

static std::vector<float> k_Steel {			0.25f, 1.00f, 1.50f, 1.00f, 0.50f, 2.00f, 1.00f, 0.50f, 1.00f, 1.00f, 1.50f, 1.00f,
										   	   	   1.00f, 0.50f, 1.00f, 1.50f, 0.25f, 1.50f, 1.00f, 1.00f, 2.00f, 1.50f, 0.50f, 0.25f};

static std::vector<float> k_Fighting {		1.00f, 1.00f, 1.50f, 1.00f, 1.00f, 1.00f, 1.00f, 0.50f, 1.00f, 1.50f, 0.00f, 2.50f,
										   	   	   1.50f, 1.00f, 1.00f, 1.00f, 1.00f, 1.50f, 1.00f, 1.00f, 1.00f, 1.00f, 1.25f, 1.50f};

static std::vector<float> k_Dark {			1.00f, 1.00f, 1.00f, 1.50f, 1.00f, 1.00f, 1.00f, 1.00f, 2.00f, 1.50f, 0.25f, 1.50f,
										   	   	   1.00f, 1.00f, 0.00f, 2.50f, 1.00f, 1.00f, 1.00f, 1.00f, 1.00f, 1.00f, 1.00f, 0.75f};

static std::vector<float> k_Light {			1.00f, 1.00f, 1.50f, 1.25f, 1.00f, 1.00f, 1.00f, 1.00f, 0.50f, 1.00f, 2.50f, 1.00f,
										   	   	   1.00f, 1.00f, 2.50f, 0.00f, 1.00f, 1.00f, 2.50f, 1.00f, 1.00f, 1.00f, 1.00f, 0.75f};

static std::vector<float> k_Magma {			0.00f, 0.25f, 1.50f, 1.50f, 1.00f, 0.50f, 0.25f, 0.50f, 2.50f, 1.00f, 1.00f, 1.00f,
										   	   	   1.25f, 1.00f, 1.00f, 1.00f, 1.00f, 1.25f, 1.25f, 1.00f, 1.25f, 1.00f, 1.00f, 1.00f};

static std::vector<float> k_Magnet {		1.00f, 1.00f, 1.00f, 1.00f, 2.00f, 1.25f, 1.25f, 0.50f, 0.00f, 0.25f, 1.25f, 1.00f,
										   	   	   2.50f, 0.50f, 1.00f, 1.00f, 1.00f, 1.50f, 1.00f, 1.00f, 1.00f, 1.25f, 1.50f, 0.50f};

static std::vector<float> k_Underground {	1.00f, 1.25f, 1.00f, 1.25f, 1.00f, 0.75f, 0.75f, 0.00f, 1.50f, 1.00f, 0.00f, 1.25f,
										   		   1.00f, 1.25f, 0.75f, 0.75f, 1.25f, 1.25f, 1.50f, 1.00f, 1.00f, 1.50f, 1.00f, 1.00f};

static std::vector<float> k_Poison {		1.00f, 1.25f, 1.25f, 1.25f, 1.00f, 0.50f, 1.00f, 1.00f, 1.50f, 1.50f, 0.00f, 2.50f,
										   		   0.00f, 1.50f, 1.00f, 1.00f, 0.75f, 0.25f, 1.00f, 0.00f, 1.00f, 0.50f, 1.00f, 2.50f};

static std::vector<float> k_Radiation {		1.00f, 1.00f, 1.00f, 1.00f, 1.00f, 1.25f, 1.25f, 1.50f, 2.00f, 1.50f, 1.00f, 1.50f,
										   		   0.75f, 1.50f, 1.25f, 0.50f, 0.50f, 1.00f, 0.50f, 1.00f, 1.00f, 1.00f, 1.50f, 1.00f};

static std::vector<float> k_Ancient {		1.00f, 1.00f, 0.25f, 0.75f, 1.00f, 1.50f, 1.00f, 1.00f, 1.00f, 0.75f, 1.25f, 1.25f,
										   		   0.75f, 1.00f, 1.00f, 1.00f, 2.00f, 1.00f, 1.00f, 1.50f, 1.25f, 1.00f, 2.50f, 0.50f};

static std::vector<float> k_Technology {	0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 2.00f, 1.00f, 1.00f, 0.75f, 1.00f, 2.50f, 2.00f,
										   		   2.00f, 1.00f, 1.00f, 1.00f, 2.50f, 1.00f, 1.00f, 0.75f, 1.50f, 2.50f, 1.00f, 2.50f};

static std::vector<float> k_Magic {			2.00f, 2.00f, 1.50f, 1.00f, 1.25f, 1.00f, 2.00f, 2.00f, 0.50f, 0.00f, 2.50f, 0.50f,
										   	       0.25f, 0.50f, 1.50f, 1.50f, 1.00f, 0.25f, 1.00f, 1.25f, 1.00f, 0.50f, 2.50f, 1.00f};



const Database & Database::instance() {
    static Database db;
    return db;
}

const std::string Database::getStringFromBaseType(const BaseType type) {
    return instance().getName(type);
}

const BaseType Database::getBaseTypeFromString(const std::string & name) {
	return instance().getBaseType(name);
}

const std::string Database::getStringFromEffectivenessType(const EffectiveType type) {
	return instance().getName(type);
}

const EffectiveType Database::getEffectiveness(const BaseType type1, const BaseType type2) {
	return instance().getEffect(type1, type2);
}

const float Database::getEffectivenessValue(const EffectiveType type) {

	switch(type) {
		case EffectiveType::Zero:
			return k_Zero;
		case EffectiveType::HighlyIneffective:
			return k_HighlyIneffective;
		case EffectiveType::Ineffective:
			return k_Ineffective;
		case EffectiveType::SlightlyIneffective:
			return k_SlightlyIneffective;
		case EffectiveType::Neutral:
			return k_Neutral;
		case EffectiveType::SlightlyEffective:
			return k_SlightlyEffective;
		case EffectiveType::Effective:
			return k_Effective;
		case EffectiveType::HighlyEffective:
			return k_HighlyEffective;
		case EffectiveType::MostEffective:
			return k_MostEffective;
		default:
			return -1.f;
	}

}


Database::Database() {
    addEffectivenesses();
    addNames();
}

const std::string Database::getName(const BaseType type) const {

	std::string s;
	auto it = m_baseTypeNames.find(type);
	if (it != m_baseTypeNames.end()) {
		s = it->second;
	}
	return s;

}

const BaseType Database::getBaseType(const std::string & name) const {

	for (const auto & i : m_baseTypeNames) {
		if (i.second == name) return i.first;
	}
	return BaseType();

}

const std::string Database::getName(const EffectiveType type) const {

	std::string s;
	auto it = m_effectivenessTypeNames.find(type);
	if (it != m_effectivenessTypeNames.end()) {
		s = it->second;
	}
	return s;

}

const EffectiveType Database::getEffect(const BaseType type1, const BaseType type2) const {

	auto it1 = m_effectivenesses.find(type1);
	if (it1 != m_effectivenesses.end()) {
		auto it2 = it1->second.find(type2);
		if (it2 != it1->second.end()) {
			return it2->second;
		}
	}
	return EffectiveType::Zero;

}

void Database::addNames() {

	m_baseTypeNames.emplace(BaseType::None, "None");
	m_baseTypeNames.emplace(BaseType::Fire, "Fire");
	m_baseTypeNames.emplace(BaseType::Water, "Water");
	m_baseTypeNames.emplace(BaseType::Ice, "Ice");
	m_baseTypeNames.emplace(BaseType::Snow, "Snow");
	m_baseTypeNames.emplace(BaseType::Electro, "Electro");
	m_baseTypeNames.emplace(BaseType::Stone, "Stone");
	m_baseTypeNames.emplace(BaseType::Earth, "Earth");
	m_baseTypeNames.emplace(BaseType::Air, "Air");
	m_baseTypeNames.emplace(BaseType::Plant, "Plant");
	m_baseTypeNames.emplace(BaseType::Normal, "Normal");
	m_baseTypeNames.emplace(BaseType::Ghost, "Ghost");
	m_baseTypeNames.emplace(BaseType::Psycho, "Psycho");
	m_baseTypeNames.emplace(BaseType::Steel, "Steel");
	m_baseTypeNames.emplace(BaseType::Fighting, "Fighting");
	m_baseTypeNames.emplace(BaseType::Dark, "Dark");
	m_baseTypeNames.emplace(BaseType::Light, "Light");
	m_baseTypeNames.emplace(BaseType::Magma, "Magma");
	m_baseTypeNames.emplace(BaseType::Magnet, "Magnet");
	m_baseTypeNames.emplace(BaseType::Underground, "Underground");
	m_baseTypeNames.emplace(BaseType::Poison, "Poison");
	m_baseTypeNames.emplace(BaseType::Radiation, "Radiation");
	m_baseTypeNames.emplace(BaseType::Ancient, "Ancient");
	m_baseTypeNames.emplace(BaseType::Technology, "Technology");
	m_baseTypeNames.emplace(BaseType::Magic, "Magic");

	m_effectivenessTypeNames.emplace(EffectiveType::Zero, "Zero");
	m_effectivenessTypeNames.emplace(EffectiveType::HighlyIneffective, "Highly Ineffective");
	m_effectivenessTypeNames.emplace(EffectiveType::Ineffective, "Ineffective");
	m_effectivenessTypeNames.emplace(EffectiveType::SlightlyIneffective, "Slightly Ineffective");
	m_effectivenessTypeNames.emplace(EffectiveType::Neutral, "Neutral");
	m_effectivenessTypeNames.emplace(EffectiveType::SlightlyEffective, "Slightly Effective");
	m_effectivenessTypeNames.emplace(EffectiveType::Effective, "Effective");
	m_effectivenessTypeNames.emplace(EffectiveType::HighlyEffective, "Highly Effective");
	m_effectivenessTypeNames.emplace(EffectiveType::MostEffective, "Most Effective");

}

void Database::addEffectivenesses() {

	m_effectivenesses.emplace(BaseType::Fire, createEffectivenessMap(k_Fire));
	m_effectivenesses.emplace(BaseType::Water, createEffectivenessMap(k_Water));
	m_effectivenesses.emplace(BaseType::Ice, createEffectivenessMap(k_Ice));
	m_effectivenesses.emplace(BaseType::Snow, createEffectivenessMap(k_Snow));
	m_effectivenesses.emplace(BaseType::Electro, createEffectivenessMap(k_Electro));
	m_effectivenesses.emplace(BaseType::Stone, createEffectivenessMap(k_Stone));
	m_effectivenesses.emplace(BaseType::Earth, createEffectivenessMap(k_Earth));
	m_effectivenesses.emplace(BaseType::Air, createEffectivenessMap(k_Air));
	m_effectivenesses.emplace(BaseType::Plant, createEffectivenessMap(k_Plant));
	m_effectivenesses.emplace(BaseType::Normal, createEffectivenessMap(k_Normal));
	m_effectivenesses.emplace(BaseType::Ghost, createEffectivenessMap(k_Ghost));
	m_effectivenesses.emplace(BaseType::Psycho, createEffectivenessMap(k_Psycho));
	m_effectivenesses.emplace(BaseType::Steel, createEffectivenessMap(k_Steel));
	m_effectivenesses.emplace(BaseType::Fighting, createEffectivenessMap(k_Fighting));
	m_effectivenesses.emplace(BaseType::Dark, createEffectivenessMap(k_Dark));
	m_effectivenesses.emplace(BaseType::Light, createEffectivenessMap(k_Light));
	m_effectivenesses.emplace(BaseType::Magma, createEffectivenessMap(k_Magma));
	m_effectivenesses.emplace(BaseType::Magnet, createEffectivenessMap(k_Magnet));
	m_effectivenesses.emplace(BaseType::Underground, createEffectivenessMap(k_Underground));
	m_effectivenesses.emplace(BaseType::Poison, createEffectivenessMap(k_Poison));
	m_effectivenesses.emplace(BaseType::Radiation, createEffectivenessMap(k_Radiation));
	m_effectivenesses.emplace(BaseType::Ancient, createEffectivenessMap(k_Ancient));
	m_effectivenesses.emplace(BaseType::Technology, createEffectivenessMap(k_Technology));
	m_effectivenesses.emplace(BaseType::Magic, createEffectivenessMap(k_Magic));

}

const std::map<BaseType, EffectiveType> Database::createEffectivenessMap(const std::vector<float> & v) {

	std::map<BaseType, EffectiveType> m;
	m.emplace(BaseType::Fire, getEffectivenessType(v[0]));
	m.emplace(BaseType::Water, getEffectivenessType(v[1]));
	m.emplace(BaseType::Ice, getEffectivenessType(v[2]));
	m.emplace(BaseType::Snow, getEffectivenessType(v[3]));
	m.emplace(BaseType::Electro, getEffectivenessType(v[4]));
	m.emplace(BaseType::Stone, getEffectivenessType(v[5]));
	m.emplace(BaseType::Earth, getEffectivenessType(v[6]));
	m.emplace(BaseType::Air, getEffectivenessType(v[7]));
	m.emplace(BaseType::Plant, getEffectivenessType(v[8]));
	m.emplace(BaseType::Normal, getEffectivenessType(v[9]));
	m.emplace(BaseType::Ghost, getEffectivenessType(v[10]));
	m.emplace(BaseType::Psycho, getEffectivenessType(v[11]));
	m.emplace(BaseType::Steel, getEffectivenessType(v[12]));
	m.emplace(BaseType::Fighting, getEffectivenessType(v[13]));
	m.emplace(BaseType::Dark, getEffectivenessType(v[14]));
	m.emplace(BaseType::Light, getEffectivenessType(v[15]));
	m.emplace(BaseType::Magma, getEffectivenessType(v[16]));
	m.emplace(BaseType::Magnet, getEffectivenessType(v[17]));
	m.emplace(BaseType::Underground, getEffectivenessType(v[18]));
	m.emplace(BaseType::Poison, getEffectivenessType(v[19]));
	m.emplace(BaseType::Radiation, getEffectivenessType(v[20]));
	m.emplace(BaseType::Ancient, getEffectivenessType(v[21]));
	m.emplace(BaseType::Technology, getEffectivenessType(v[22]));
	m.emplace(BaseType::Magic, getEffectivenessType(v[23]));
	return m;

}

const EffectiveType Database::getEffectivenessType(const float f) {

	if (f == 0.f) 
		return EffectiveType::Zero;
	else if (f == 0.25f)
		return EffectiveType::HighlyIneffective;
	else if (f == 0.5f)
		return EffectiveType::Ineffective;
	else if (f == 0.75f)
		return EffectiveType::SlightlyIneffective;
	else if (f == 1.f)
		return EffectiveType::Neutral;
	else if (f == 1.25f)
		return EffectiveType::SlightlyEffective;
	else if (f == 1.5f)
		return EffectiveType::Effective;
	else if (f == 2.f)
		return EffectiveType::HighlyEffective;
	else if (f == 2.5f)
		return EffectiveType::MostEffective;
	else
		return EffectiveType::Zero;

}
