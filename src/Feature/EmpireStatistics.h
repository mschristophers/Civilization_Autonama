// #pragma once

#ifndef EMPIRESTATISTICS_H_INCLUDED
#define EMPIRESTATISTICS_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>

#include "Empire.h"

struct EmpireStatistics {
	unsigned highestStrength = 0;
	unsigned strength = 0;
	unsigned population = 0;
	sf::Text text;
	std::string name;
};

// Handles empire statistics (e.g., updating, rendering)
class EmpireStatsManager {
public:
	EmpireStatsManager(unsigned empireCount);

	void initText(const std::vector<Empire>& empires);

	void reset();
	void update(unsigned empireID, unsigned strength);

	void drawStats(sf::RenderWindow& window);

private:
	std::vector<EmpireStatistics> civ_empireStats;
	sf::RectangleShape civ_empireStatsBg;
	sf::Text civ_totalPopText;
};

#endif // For EMPIRESTATISTICS_H_INCLUDED