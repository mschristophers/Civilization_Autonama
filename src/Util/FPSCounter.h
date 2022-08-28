// #pragma once

#ifndef FPSCOUNTER_H_INCLUDED
#define FPSCOUNTER_H_INCLUDED

#include <SFML/Graphics.hpp>

class FPSCounter {
	public:
		FPSCounter();

		void update();

		void draw(sf::RenderTarget& renderer);

	private:
		sf::Text civ_text;
		sf::Font civ_font;

		sf::Clock civ_delayTimer;
		sf::Clock civ_fpsTimer;

		float civ_fps = 0;

		int civ_frameCount = 0;
};

#endif // For FPSCOUNTER_H_INCLUDED