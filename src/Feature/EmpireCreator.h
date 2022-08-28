// #pragma once

#ifndef EMPIRECREATOR_H_INCLUDED
#define EMPIRECREATOR_H_INCLUDED

#include <vector>

#include "Empire.h"

class EmpireCreator {
	public:
		virtual std::vector<sf::Vector2i> createEmpireLocations(
		const Config& config, const Map& map) const = 0;
		virtual std::vector<Empire> createEmpireStats() const = 0;
};

#endif // For EMPIRECREATOR_H_INCLUDED