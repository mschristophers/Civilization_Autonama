// #pragma once

#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include "../Util/Grid.h"

#include "Empire.h"
#include "EmpireStatistics.h"
#include "Map.h"
#include "Person.h"

class World {
	public:
		World(const Config& config);

		void update(sf::Image& image);
		void drawText(sf::RenderWindow& window);

		const sf::Color& getColorAt(unsigned x, unsigned y) const;

		void draw(sf::RenderWindow& window);

	private:
		void tryWrap(int& x, int& y) const;

		void createEmpires();

		Map civ_map;
		Grid<Person> civ_people;
		std::vector<Empire> civ_empires;
		EmpireStatsManager civ_empireStatsManager;

		const Config* civ_pConfig;
};

#endif // For WORLD_H_INCLUDED