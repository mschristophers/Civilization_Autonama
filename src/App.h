// #pragma once

#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <mutex>
#include <vector>

#include "Feature/World.h"
#include "Util/FPSCounter.h"
#include "Util/NonCopyable.h"
#include "Util/NonMoveable.h"

struct Config;

class App {
	public:
		App(const Config& config);

		void run();

	private:
		void createImage();
		void updateImage();

		void pollEvents();
		void input(float dt);
		void update();
		void render();

		sf::RenderWindow civ_window;

		World civ_world;

		FPSCounter civ_fpsCounter;

		const Config* civ_pConfig;

		sf::Image civ_pixelBuffer;
		sf::Texture civ_pixelSurfaceTexture;
		sf::RectangleShape civ_pixelSurface;

		sf::Text civ_GUIText;
		sf::RectangleShape civ_button;

		sf::View civ_view;

		std::mutex civ_imageMutex;
};

#endif // For APP_H_INCLUDED