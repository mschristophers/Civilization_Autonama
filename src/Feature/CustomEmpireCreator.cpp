#include "CustomEmpireCreator.h"

#include "Map.h"

#include "../Util/Config.h"
#include "../Util/Random.h"

#include <fstream>
#include <iostream>

CustomEmpireCreator::CustomEmpireCreator(const std::string& fileName)
{
	std::ifstream inFile("res/Starts/" + fileName + ".txt");

	if (!inFile.is_open()) {
		std::cout << "Unable to open custom empires for: " << fileName << '\n';
		exit(-1);
	}

	std::string line;

	while (std::getline(inFile, line)) {
		if (line == "EMPIRE") {
			std::cout << "Found empire!\n";

			bool startFound = false;
			bool strengthFound = false;
			bool peopleFound = false;
			bool colorFound = false;

			EmpireInfo info;

			while (line != "END") {
				std::getline(inFile, line);

				if (line == "START") {
					loadStartPoint(info, inFile);
					startFound = true;
				}
				else if (line == "STRENGTH") {
					loadStrength(info, inFile);
					strengthFound = true;
				}
				else if (line == "PEOPLE") {
					peopleFound = true;
					inFile >> info.people;

					if (info.people < 0) {
						printError("PEOPLE");
						info.people = 100;
					}
				}
				else if (line == "COLOR") {
					int r, g, b;
					colorFound = true;
					inFile >> r >> g >> b;
					info.color.r = (uint8_t)r;
					info.color.g = (uint8_t)g;
					info.color.b = (uint8_t)b;
				}
			}

			if (startFound && strengthFound && peopleFound && colorFound) {
				civ_empireInfo.push_back(info);
			}
			else {
				std::cout << "Failed to load empire, section missing\n";
			}
		}
	}
}

std::vector<sf::Vector2i> CustomEmpireCreator::createEmpireLocations(
const Config& config, const Map& map) const
{
	std::vector<sf::Vector2i> locations(civ_empireInfo.size() + 1);

	// Skips Empire 0
	for (unsigned i = 1; i < civ_empireInfo.size() + 1; i++) {
		int x, y;
		x = civ_empireInfo[i - 1].startPoint.x;
		y = civ_empireInfo[i - 1].startPoint.y;

		if (!map.isLandAt(x, y)) {
			std::cout << "WARNING: EMPIRE OVER WATER.\n";
		}

		locations[i] = { x, y };
	}

	return locations;
}

std::vector<Empire> CustomEmpireCreator::createEmpireStats() const
{
	std::vector<Empire> empires(civ_empireInfo.size() + 1);

	// Empire 0 is reserved for the dead
	empires[0].color = { 0, 0, 0, 10 };
	empires[0].id = 0;

	// Skips Empire 0
	for (unsigned i = 1; i < civ_empireInfo.size() + 1; i++) {
		auto& emp = empires[i];
		auto& info = civ_empireInfo[i - 1];

		emp.strLow = info.strLow;
		emp.strHigh = info.strHigh;
		emp.color = info.color;
		emp.initialPopulation = info.people;
		emp.id = i;
	}

	return empires;
}

void CustomEmpireCreator::loadStartPoint(EmpireInfo& info, std::ifstream& inFile)
{
	inFile >> info.startPoint.x >> info.startPoint.y;

	if (info.startPoint.x < 0) {
		printError("START POINT X");
		info.startPoint.x = 100;
	}
	if (info.startPoint.y < 0) {
		printError("START POINT Y");
		info.startPoint.y = 100;
	}
}

void CustomEmpireCreator::loadStrength(EmpireInfo& info, std::ifstream& inFile)
{
	inFile >> info.strLow >> info.strHigh;
	
	if (info.startPoint.x < 0) {
		printError("STRENGTH");
		info.strLow = 100;
	}
	if (info.startPoint.y < 0) {
		printError("STRENGTH");
		info.strHigh = 100;
	}
}

void CustomEmpireCreator::printError(const std::string& name)
{
	std::cout << name << "MUST BE GREATER THAN 0, setting to 100.\n\n";
}