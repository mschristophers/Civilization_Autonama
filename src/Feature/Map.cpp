#include "Map.h"

#include "../Util/Config.h"

constexpr int COLOR_RECOGNIZE_THRESHOLD = 220;

Map::Map(const Config& config)
	: civ_pConfig(&config)
{
	civ_mapTexture.loadFromImage(config.image);
	civ_sprite.setTexture(&civ_mapTexture);
	civ_sprite.setSize({ (float)config.width, (float)config.height });
}

void Map::draw(sf::RenderWindow& window) const
{
	window.draw(civ_sprite);
}

bool Map::isWaterAt(unsigned x, unsigned y) const
{
	return civ_pConfig->image.getPixel(x, y).b >= COLOR_RECOGNIZE_THRESHOLD;
}

bool Map::isLandAt(unsigned x, unsigned y) const
{
	return civ_pConfig->image.getPixel(x, y).g >= COLOR_RECOGNIZE_THRESHOLD;
}