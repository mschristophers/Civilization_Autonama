#include "World.h"

#include "EmpireCreator.h"
#include "CustomEmpireCreator.h"
#include "RandomEmpireCreator.h"

#include "../ResourceStuff/ResourceHolder.h"
#include "../Util/Common.h"
#include "../Util/Config.h"
#include "../Util/Random.h"

#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>

//#define SWIMMING_ENABLED
//#define LASER_SWIMMING

constexpr int CHAR_SIZE = 14;

World::World(const Config& config)
	: civ_map(config)
	, civ_people(config.width, config.height)
	, civ_empireStatsManager(config.empires)
	, civ_pConfig(&config)
{
	createEmpires();
	civ_empireStatsManager.initText(civ_empires);
}

const sf::Color& World::getColorAt(unsigned x, unsigned y) const
{
	return civ_empires[civ_people(x, y).empire].color;
}

void World::tryWrap(int& x, int& y) const
{
	if (x < 0)
		x += (civ_pConfig->width - 1);
	else if (x >= (int)civ_pConfig->width)
		x -= civ_pConfig->width;

	if (y < 0)
		y += (civ_pConfig->height - 1);
	else if (y >= (int)civ_pConfig->height)
		y -= civ_pConfig->height;
}

void World::drawText(sf::RenderWindow& window)
{
	civ_empireStatsManager.drawStats(window);
}

void World::draw(sf::RenderWindow& window)
{
	civ_map.draw(window);
}

void World::createEmpires()
{
	std::unique_ptr<EmpireCreator> empireCreator;

	if (civ_pConfig->customStart)
		empireCreator = std::make_unique<CustomEmpireCreator>(civ_pConfig->imageName);
	else
		empireCreator = std::make_unique<CustomEmpireCreator>(civ_pConfig->empires);

	auto locations = empireCreator->createEmpireLocations(*civ_pConfig, civ_map);
	civ_empires = empireCreator->createEmpireStats();

	// Place empires at their locations
	for (unsigned i = 1; i < civ_empires.size(); i++) {
		auto& location = locations[i];

		// Place people at their locations
		for (unsigned j = 0; j < civ_empires[i].initialPopulation; j++) {
			constexpr int radius = 5;
			int xOffset = Random::get().intInRange(-radius, radius);
			int yOffset = Random::get().intInRange(-radius, radius);

			int newLocationX = xOffset + location.x;
			int newLocationY = yOffset + location.y;

			if (newLocationX < 0 || newLocationX >= (int)civ_pConfig->width)
				continue;
			if (newLocationY < 0 || newLocationY >= (int)civ_pConfig->height)
				continue;
			if (civ_map.isWaterAt(newLocationX, newLocationY))
				continue;

			DescendantData data;
			data.strength =
				Random::get().intInRange(civ_empires[i].strLow, civ_empires[i].strHigh);
			data.isDiseased = false;
			data.empire = i;

			civ_people(newLocationX, newLocationY).init(data);
		}
	}
}

void World::update(sf::Image& image)
{
	Grid<Person> newPeople(civ_pConfig->width, civ_pConfig->height);
	civ_empireStatsManager.reset();

	randomCellForEach(*civ_pConfig, [&](unsigned x, unsigned y) {
		auto& person = civ_people(x, y);

		if (!person.isAlive)
			return;

		person.update();

		if (!person.isAlive) {
			image.setPixel(x, y, getColorAt(x, y));
			return;
		}

		auto empireID = person.empire;
		auto strength = person.strength;

		// Loops might occasionally return early
		// If yes, it will call these functions
		auto endAlive = [&]() {
			newPeople(x, y) = person;
			civ_empireStatsManager.update(empireID, strength);
			image.setPixel(x, y, getColorAt(x, y));
		};

		auto endDead = [&]() { 
			image.setPixel(x, y, getColorAt(x, y));
		};

		// Gets the new location to move into
		auto nextMove = person.getNextMove();
		int xMoveTo = x + nextMove.x;
		int yMoveTo = y + nextMove.y;
		tryWrap(xMoveTo, yMoveTo);

		// Grid square to move to
		auto& movePerson = civ_people(xMoveTo, yMoveTo);

		if (civ_map.isWaterAt(xMoveTo, yMoveTo)) {
#ifndef SWIMMING_ENABLED
			endAlive();
			return;
#endif // For SWIMMING_ENABLED

#ifndef SWIMMING_ENABLED
			if (!person.isSwimming) {
				if ((Random::get().intInRange(0, 10000) < 30)) {
					person.startSwim(nextMove);
				}
				else {
					endAlive();
					return;
				}
			}
#endif // For SWIMMING_ENABLED

#ifndef SWIMMING_ENABLED
			else {
				person.endSwim();
			}
#endif // For SWIMMING_ENABLED

			// For encounters with people of the same empire or others
			if (movePerson.empire == empireID) { // Disease will spread
				if (movePerson.isDiseased) {
					person.giveDisease();
				}

				if (person.isSwimming) {
					person.turnAround();
				}

				endAlive();
				return;
			}

			else {
				if (movePerson.isAlive) {
					person.fight(movePerson);
					if (!person.isAlive) {
						endDead();
						return;
					}
				}
			}

			// If the person survived, they will move to the next place
			newPeople(xMoveTo, yMoveTo) = person;

			// Only reproduce over land
			if (person.isSwimming) {
// Kills the old person, the current person has now moved.
#ifndef LASER_SWIMMING
				person.kill();
#endif // For LASER_SWIMMING

#ifndef LASER_SWIMMING
				// Turning this allows people to swim in straight lines
				person.init(person.getDescendant());
#endif // LASER_SWIMMING
			}

			else {
				if ((person.productionCount >= (unsigned)civ_pConfig->birthThreshold)) {
					// The person has moved to a new spot,
					// so modifying the data should be fine.
					person.init(person.getDescendant());
				}
				else {
					// Kills the old person, the current person has moved.
					person.kill();
				}
			}

			endAlive();
		}
		});

		civ_people = std::move(newPeople);
}