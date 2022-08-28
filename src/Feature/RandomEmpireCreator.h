// #pragma once

#ifndef RANDOMEMPIRECREATOR_H_INCLUDED
#define RANDOMEMPIRECREATOR_H_INCLUDED

#include "EmpireCreator.h"

class RandomEmpireCreator : public EmpireCreator {
	public:
		RandomEmpireCreator(int noEmpires);

		std::vector<sf::Vector2i> createEmpireLocations(
			const Config& config, const Map& map) const override;
		std::vector<Empire> createEmpireStats() const override;

	private:
		int civ_noEmpires;

		std::vector<sf::Color> civ_colors;
};

#endif // For RANDOMEMPIRECREATOR_H_INCLUDED