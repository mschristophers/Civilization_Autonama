// #pragma once

#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED

#include <random>

class Random {
public:
	static Random& get();

	Random(const Random& other) = delete;
	Random& operator = (const Random& other) = delete;

	int intInRange(int low, int high);
	float floatInRange(float low, float high);

	template <typename T>
	T getNInRange(T low, T high)
	{
		std::uniform_real_distribution<T> dist(low, high);
		return dist(civ_rng);
	}

private:
	Random();

	std::mt19937 civ_rng;
};

#endif // For RANDOM_H_INCLUDED