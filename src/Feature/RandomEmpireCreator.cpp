#include "RandomEmpireCreator.h"

#include "Map.h"

#include "../Util/Config.h"
#include "../Util/Random.h"

#include <fstream>
#include <iostream>

RandomEmpireCreator::RandomEmpireCreator(int noEmpires)
	: civ_noEmpires(noEmpires)
{
	std::ifstream inFile("colors.txt");

	if (!inFile.is_open()) {
		std::cout << "Unable to open colors.txt.\n\n";
	}

	sf::Color color;

	int r, g, b;

	while (inFile >> r >> g >> b) {
		sf::Uint8 red = (sf::Uint8)r;
		sf::Uint8 green = (sf::Uint8)g;
		sf::Uint8 blue = (sf::Uint8)b;

		civ_colors.push_back({ red, green, blue });
	}
}

std::vector<sf::Vector2i> RandomEmpireCreator::createEmpireLocations(
	const Config& config, const Map& map) const
{
	std::vector<sf::Vector2i> locations(civ_noEmpires);

	// Skips Empire 0
	for (int i = 1; i < civ_noEmpires; i++) {
		int x, y;
		// Loops until land is found
		while (true) {
			x = Random::get().intInRange(0, config.width);
			y = Random::get().intInRange(0, config.height);
			if (map.isLandAt(x, y)) {
				locations[i] = { x, y };
				break;
			}
		}
	}

	return locations;
}

std::vector<Empire> RandomEmpireCreator::createEmpireStats() const
{
	std::vector<Empire> empires(civ_noEmpires);

	// Empire 0 is reserved for the dead
	empires[0].color = { 0, 0, 0, 0 };
	empires[0].id = 0;

	// Skips Empire 0
	for (int i = 1; i < civ_noEmpires; i++) {
		auto& emp = empires[i];

		emp.strLow = 400;
		emp.strHigh = 650;

		if (i > (int)civ_colors.size() - 1) {
			sf::Uint8 r = Random::get().intInRange(0, 255);
			sf::Uint8 g = Random::get().intInRange(0, 255);
			sf::Uint8 b = Random::get().intInRange(0, 255);
			emp.color = { r, g, b };
		}
		else {
			empires[i].color = civ_colors[i];
		}

		empires[i].id = i;
	}

	return empires;
}