#ifndef _ENUMS_H_
#define _ENUMS_H_

enum class BaseType : unsigned int {
    
    None = 0,
    Fire,
    Water,
    Ice,
    Snow,
    Electro,
    Stone,
    Earth,
    Air,
    Plant,
    Normal,
    Ghost,
    Psycho,
    Steel,
    Fighting,
    Dark,
    Light,
    Magma,
    Magnet,
    Underground,
    Poison,
    Radiation,
    Ancient,
    Technology,
    Magic

};

enum class EffectiveType : unsigned int {

    Zero = 0,
    HighlyIneffective,
    Ineffective,
    SlightlyIneffective,
    Neutral,
    SlightlyEffective,
    Effective,
    HighlyEffective,
    MostEffective

};

enum class LocationType : unsigned int {

    Forest = 0,
    Meadow,
    Mountain,
    Cave,
    Urban,
    Desert,
    Jungle,
    Arctic,
    Ocean,
    Deepsea,
    Sky

};

enum class SeasonType : unsigned int {

    Winter = 0,
    Spring,
    Summer,
    Fall

};

enum class DaytimeType : unsigned int {

    Night = 0,
    Day,
    Twilight

};

inline bool operator==(BaseType id1, BaseType id2) {
    return static_cast<unsigned int>(id1) == static_cast<unsigned int>(id2);
}

inline bool operator!=(BaseType id1, BaseType id2) {
    return static_cast<unsigned int>(id1) != static_cast<unsigned int>(id2);
}

#endif // _ENUMS_H_
