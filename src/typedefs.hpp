#ifndef _TYPEDEFS_HPP
#define _TYPEDEFS_HPP

#include <map>
#include <array>
#include <tuple>
#include <vector>

#include "position.hpp"

#define debugOutput(X) DEB(__FILE__ + " " + __FUNCTION__ + " " + __LINE__ + " " + X)

using portalMap = std::map<Position, std::string>;
using partyTuples = std::vector<std::tuple<std::string,unsigned int>>;

static constexpr unsigned int k_height = 40;
static constexpr unsigned int k_width = 100;
using twoDimArray = std::array<std::array<char, k_width>, k_height>;

using likelyhoodTuples = std::vector<std::tuple<std::string, unsigned int, unsigned int, float>>;
using locationTuple = std::tuple<std::string,Position>;

#endif // _TYPEDEFS_HPP