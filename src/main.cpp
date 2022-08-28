#include <fstream>
#include <iostream>
#include <thread>

#include "App.h"
#include "Util/Config.h"
#include "Util/Random.h"

void parseConfig(std::ifstream& inFile, Config& fileConfig);

int main()
{
	std::cout << "\n~~~~~Please read this!~~~~~\n"
			  << "~~~~~~~~~~\n\n";

	Config fileConfig;

	std::cout << "Trying to load image... \n";

	std::ifstream inFile("config.txt");

	if (!inFile.is_open()) {
		std::cerr << "Unable to open config, using default.\n";
		fileConfig.image.loadFromFile("res/Maps/world_map_large.png");
	}
	else {
		parseConfig(inFile, fileConfig);
	}

	std::cout << "Please view the instructions file for controls and"
				 "\n ways to customize your experience. \n\n";

	fileConfig.width = fileConfig.image.getSize().x;
	fileConfig.height = fileConfig.image.getSize().y;

	App app(fileConfig);
	app.run();
}

void parseConfig(std::ifstream& inFile, Config& fileConfig)
{
	std::string str;
	while (std::getline(inFile, str)) {
		if (str == "IMAGE") {
			inFile >> str;
			if (!fileConfig.image.loadFromFile("res/Maps/" + str)) {
				std::cerr << "Unable to open \"" << str << "\", using default.\n\n";
				fileConfig.image.loadFromFile("res/Maps/world_map_large.png");
			}
			else {
				fileConfig.imageName = str.substr(0, str.length() - 4);
				std::cout << fileConfig.imageName << "\n";
				std::cout << "Success! Using " << str << ".\n\n";
			}
		}
		else if (str == "CUSTOM_START") {
			inFile >> fileConfig.customStart;
			std::cout << "Custom Start loaded, set to " << std:boolalpha
					  << fileConfig.customStart << ".\n\n";
		}
		else if (str == "BIRTH") {
			inFile >> fileConfig.birthThreshold;
			std::cout << "Reproduction Threshold loaded, set to "
					  << fileConfig.birthThreshold << ".\n\n";
		}
		else if (str == "EMPIRES") {
			inFile >> fileConfig.empires;
			std::cout << "Empire Count loaded, set to "
					  << fileConfig.empires++ << ".\n\n";

			if (fileConfig.empires <= 2) {
				std::cout << "Empire count too low! Setting to MIN [3]\n";
				fileConfig.empires = 3;
			}
			else if (fileConfig.empires > 400) {
				std::cout << "Empire count too high! Setting to MAX [400]\n";
				fileConfig.empires = 400;
			}
		}
	}
}