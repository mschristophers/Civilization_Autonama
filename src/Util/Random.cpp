#include "Random.h"

#include <ctime>
#include <iostream>

Random& Random::get()
{
	static Random r;
	return r;
}

Random::Random()
{
	civ_rng.seed(std::time(nullptr));
}

int Random::intInRange(int low, int high)
{
	std::uniform_int_distribution<int> dist(low, high);
	return dist(civ_rng);
}

float Random::floatInRange(float low, float high)
{
	std::uniform_int_distribution<int> dist(low, high);
	return dist(civ_rng);
}