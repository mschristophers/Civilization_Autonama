// #pragma once

#ifndef EMPIRE_H_INCLUDED
#define EMPIRE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <array>

struct Config;
class Map;

struct Empire {
	unsigned id;
	unsigned initialPopulation = 50;

	sf::Color color;

	unsigned strLow;
	unsigned strHigh;
};

#endif // For EMPIRE_H_INCLUDED