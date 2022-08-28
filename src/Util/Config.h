// #pragma once

#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <SFML/Graphics.hpp>

struct Config {
	std::string imageName;
	sf::Image image;
	unsigned width;
	unsigned height;

	int birthThreshold = 8;
	int empires = 10;

	bool customStart = false;
};

#endif // For CONFIG_H_INCLUDED