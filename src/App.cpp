#include "App.h"

#include <ctime>
#include <iostream>
#include <mutex>
#include <thread>

#include "Util/Common.h"

#include "ResourceStuff/ResourceHolder.h"

App::App(const Config& config)
	: civ_window({config.width, config.height}, "Civilization Autonama")
	, civ_world(config)
	, civ_pConfig(&config)
{
	civ_view.setCenter({ (float)config.width / 2, (float)config.height / 2 });
	civ_view.setSize({ (float)config.width, (float)config.height });

	civ_pixelBuffer.create(civ_pConfig->width, civ_pConfig->height);
	updateImage();

	civ_pixelSurfaceTexture.loadFromImage(civ_pixelBuffer);
	civ_pixelSurface.setSize({ (float)config.width, (float)config.height });
	civ_pixelSurface.setTexture(&civ_pixelSurfaceTexture);

	civ_GUIText.setFont(ResourceHolder::get().fonts.get("arial"));
	civ_GUIText.setCharacterSize(15);
	civ_GUIText.move(10, 3);

	civ_button.setSize({ 32, 32 });
	civ_button.setPosition(8, 8);

	civ_button.setTexture(&ResourceHolder::get().textures.get("sigma"));
}

void App::run()
{
	sf::Clock deltaClock;
	unsigned year = 0;

	while (civ_window.isOpen()) {
		civ_GUIText.setString("Years: " + std::to_string(year++));
		civ_fpsCounter.update();

		input(deltaClock.restart().asSeconds());
		update();
		render();
		pollEvents();
		std::this_thread::sleep_for(std::chrono::milliseconds(2));
	}
}

void App::pollEvents()
{
	sf::Event e;

	while (civ_window.pollEvent(e)) {
		if (e.type == sf::Event::Closed) {
			civ_window.close();
		}
		else if (e.type == sf::Event::KeyPressed) {
			if (e.key.code == sf::Keyboard::P) {
				std::thread(&App::createImage, this).detach();
			}
			if (e.key.code == sf::Keyboard::Up) {
				civ_view.zoom(0.99);
			}
			if (e.key.code == sf::Keyboard::Down) {
				civ_view.zoom(1.01);
			}
		}
	}
}

// Gets the people's pixels, and saves it to an image
void App::createImage()
{
	civ_imageMutex.lock();
	static int imageCount = 0;

	std::cout << "Saving image... \nPlease hold...\n";
	std::string fileName = "Screenshots/Screenshot" + std::to_string(imageCount++) + ".png";

	if (civ_pixelBuffer.saveToFile(fileName)) {
		std::cout << "Saved to file " << fileName
				  << "! Be aware, future sessions WILL OVERRIDE these images.\n\n";
	}
	else {
		std::cout << "Failed to save!\n\n";
	}

	civ_imageMutex.unlock();
}

void App::updateImage()
{
	cellForEach(*civ_pConfig, [&](unsigned x, unsigned y) {
		civ_pixelBuffer.setPixel(x, y, civ_world.getColorAt(x, y));
	});
}

void App::input(float dt)
{
	float speed = 100;
	sf::Vector2f change;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		change.y -= speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		change.y += speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		change.x -= speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		change.x += speed;
	}

	civ_view.move(change * dt);
}

void App::update()
{
	civ_window.clear(sf::Color::Blue);

	civ_window.setView(civ_view);
	civ_world.draw(civ_window);
	civ_window.draw(civ_pixelSurface);
	civ_window.setView(civ_window.getDefaultView());

	auto pos = sf::Mouse::getPosition(civ_window);

	if (civ_button.getGlobalBounds().contains(pos.x, pos.y)) {
		civ_world.drawText(civ_window);
		civ_window.draw(civ_GUIText);
		civ_fpsCounter.draw(civ_window);
	}
	else {
		civ_window.draw(civ_button);
	}

	civ_window.display();
}