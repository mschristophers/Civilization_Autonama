// #pragma once

#ifndef CUSTOMEMPIRECREATOR_H_INCLUDED
#define CUSTOMEMPIRECREATOR_H_INCLUDED

#include "EmpireCreator.h"

class CustomEmpireCreator : public EmpireCreator {
	struct EmpireInfo {
		sf::Vector2i startPoint;
		int strLow, strHigh, people;

		sf::Color color;
	};

	public:
		CustomEmpireCreator(const std::string& fileName);

		std::vector<sf::Vector2i> createEmpireLocations(
			const Config& config, const Map& map) const override;
		std::vector<Empire> createEmpireStats() const override;

	private:
		void loadStartPoint(EmpireInfo& info, std::ifstream& inFile);
		void loadStrength(EmpireInfo& info, std::ifstream& inFile);
		void printError(const std::string& name);

		std::vector<EmpireInfo> civ_empireInfo;
};

#endif // For CUSTOMEMPIRECREATOR_H_INCLUDED