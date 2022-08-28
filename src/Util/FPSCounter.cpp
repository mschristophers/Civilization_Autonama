#include "FPSCounter.h"

#include "../ResourceStuff/ResourceHolder.h"

#include <iostream>

FPSCounter::FPSCounter()
{
	civ_text.move(10, 20);
	civ_text.setFillColor(sf::Color::White);
	civ_text.setFont(ResourceHolder::get().fonts.get("arial"));
	civ_text.setCharacterSize(14);
}

void FPSCounter::update()
{
	civ_frameCount++;

	if (civ_delayTimer.getElapsedTime().asSeconds() > 0.2) {
		civ_fps = civ_frameCount / civ_fpsTimer.restart().asSeconds();
		civ_frameCount = 0;
		civ_delayTimer.restart();
	}
}

void FPSCounter::draw(sf::RenderTarget& renderer)
{
	civ_text.setString("FPS: " + std::to_string((int)civ_fps));
	renderer.draw(civ_text);
}