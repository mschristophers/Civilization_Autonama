// #pragma once

#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <vector>

struct Vect2 {
	int8_t x : 2;
	int8_t y : 2;
};

// Struct for the descendants of the initial population
struct DescendantData {
	uint16_t strength;
	uint16_t empire;
	uint16_t isDiseased;
};

// Represents one person
struct Person {
	void init(const DescendantData& data);

	void update();

	void startSwim(Vect2 dir);
	void endSwim();
	void turnAround();

	void kill();
	void giveDisease();
	void fight(Person& other);

	Vect2 getNextMove() const;

	DescendantData getDescendant();

	uint16_t age = 0;
	uint16_t strength = 0;
	uint16_t empire = 0;
	uint8_t productionCount = 0;
	uint8_t stopSwimCount = 0;
	Vect2 swimDir;

	bool isDiseased : 1;
	bool isAlive : 1;
	bool isSwimming : 1;
};

#endif // For PERSON_H_INCLUDED