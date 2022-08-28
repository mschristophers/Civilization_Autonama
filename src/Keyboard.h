#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <array>

class Keyboard {
public:
    Keyboard()
    {
        std::fill(civ_keys.begin(), civ_keys.end(), false);
    }

    bool isKeyDown(sf::Keyboard::Key key) const
    {
        return civ_keys[key];
    }

    void update(sf::Event e)
    {
        switch (e.type) {
        case sf::Event::KeyPressed:
            civ_keys[e.key.code] = true;
            break;

        case sf::Event::KeyReleased:
            civ_keys[e.key.code] = false;

        default:
            break;
        }
    }

private:
    void resetKeys()
    {
        std::fill(civ_keys.begin(), civ_keys.end(), false);
    }

    std::array<bool, sf::Keyboard::KeyCount> civ_keys;
};