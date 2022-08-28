#include "EmpireStatistics.h"

#include "../ResourceStuff/ResourceHolder.h"

#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>

constexpr int CHAR_SIZE = 14;

EmpireStatsManager::EmpireStatsManager(unsigned empireCount)
	: civ_empireStats(empireCount)
{
}

void EmpireStatsManager::reset()
{
	for (auto& empireStat : civ_empireStats) {
		empireStat.highestStrength = 0;
		empireStat.strength = 0;
		empireStat.population = 0;
	}
}

void EmpireStatsManager::update(unsigned empireID, unsigned strength)
{
	EmpireStatistics& stats = civ_empireStats[empireID];

	stats.highestStrength = std::max(stats.highestStrength, strength);
	stats.strength += strength;
	stats.population++;
}

void EmpireStatsManager::drawStats(sf::RenderWindow& window)
{
	window.draw(civ_empireStatsBg);

	int i = 2;
	int totalPopulation = 0;
	for (auto& stats : civ_empireStats) {
		totalPopulation += stats.population;

		if (stats.population == 0)
			continue;

		stats.text.setPosition(10, i++ * CHAR_SIZE + 30);

		std::ostringstream stream;

		int averageStr = stats.population > 0 ? stats.strength / stats.population : 0;

		stream << std::left << std::setw(10) << std::left << stats.name << std::right
			   << '\t' << std::setw(7) << std::right << stats.population << std::right
			   << '\t' << std::setw(10) << std::right << " Avg Str: " << std::right
			   << averageStr << '\t' << std::setw(10) << std::right << " Max Str  "
			   << std::right << stats.highestStrength << '\n';

		stats.text.setString(stream.str());
		
		window.draw(stats.text);
	}

	civ_totalPopText.setString("Total Population: " + std::to_string(totalPopulation));
	civ_totalPopText.setPosition(10, CHAR_SIZE + 30);
	window.draw(civ_totalPopText);

	civ_empireStatsBg.setSize({355, float(i * CHAR_SIZE + 30)});
}

void EmpireStatsManager::initText(const std::vector<Empire>& empires)
{
	civ_empireStatsBg.move(4,4);
	civ_empireStatsBg.setFillColor({128, 128, 128, 230});
	civ_empireStatsBg.setOutlineColor(sf::Color::Black);
	civ_empireStatsBg.setOutlineThickness(3);

	for (unsigned i = 0; i < empires.size(); i++) {
		auto& stats = civ_empireStats[i];

		stats.name = "Empire " + std::to_string(i) + ": ";

		stats.text.setCharacterSize(CHAR_SIZE);
		stats.text.setOutlineColor(sf::Color::Black);
		stats.text.setFillColor(empires[i].color);
		stats.text.setOutlineThickness(1);
		stats.text.setFont(ResourceHolder::get().fonts.get("arial"));
	}

	civ_totalPopText.setCharacterSize(CHAR_SIZE);
	civ_totalPopText.setOutlineColor(sf::Color::Black);
	civ_totalPopText.setFillColor(sf::Color::White);
	civ_totalPopText.setOutlineThickness(1);
	civ_totalPopText.setFont(ResourceHolder::get().fonts.get("arial"));
}