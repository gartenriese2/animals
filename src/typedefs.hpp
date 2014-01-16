#ifndef _TYPEDEFS_HPP
#define _TYPEDEFS_HPP

#include <map>
#include <array>
#include <tuple>
#include <vector>

#include "position.hpp"

using portalMap = std::map<Position, std::string>;

static constexpr unsigned int k_height = 40;
static constexpr unsigned int k_width = 100;
using twoDimArray = std::array<std::array<char, k_width>, k_height>;

using likelyhoodTuples = std::vector<std::tuple<std::string, unsigned int, unsigned int, float>>;

#endif // _TYPEDEFS_HPP