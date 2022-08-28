// #pragma once

#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include <vector>

template <typename T>

class Grid {
public:
	Grid(unsigned width, unsigned height)
		: civ_width(width)
		, civ_height(height)
		, civ_data(width* height)
	{
	}

	unsigned width() const
	{
		return civ_width;
	}
	unsigned height() const
	{
		return civ_height;
	}

	T& operator()(unsigned x, unsigned y)
	{
		return civ_data[x + y * civ_width];
	}
	const T& operator()(unsigned x, unsigned y) const
	{
		return civ_data[x + y * civ_width];
	}

private:
	unsigned civ_width;
	unsigned civ_height;
	std::vector<T> civ_data;
};

#endif // For GRID_H_INCLUDED