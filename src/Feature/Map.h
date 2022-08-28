// #pragma once

#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <SFML/Graphics.hpp>

struct Config;

class Map {
public:
	Map(const Config& config);

	void draw(sf::RenderWindow& window) const;

	bool isWaterAt(unsigned x, unsigned y) const;
	bool isLandAt(unsigned x, unsigned y) const;

private:
	sf::Texture civ_mapTexture;
	sf::RectangleShape civ_sprite;

	const Config* civ_pConfig = nullptr;
};

#endif // For MAP_H_INCLUDED